/*
* This file is part of Thoth.
* 
* Copyright (C) 2016  Joshua Barretto <joshua.s.barretto@gmail.com>
* 
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

/*
* Name:         enterlong.s
* 
* Description:  x86_64 pre-kernel boot code
* 
* Notes:        NONE
*/

// This code is used to enter long (64-bit) mode. The approximate procedure to
// do this is as follows:
//
// 1) If paging is enabled, disable paging
// 2) If the CR4.PAE control register bit is not set, set it
// 3) Set IA32_EFER.LME = 1
// 4) Load a valid PML4 (Page Map Level 4) into CR3
// 5) Enable paging
// -- At this point, compatibility mode has been entered --
// 6) Perform a far-jump (fjmp) with an offset that does not exceed 32-bit
// -- We're now in long (64-bit) mode

// First off, we'll need a temporary GDT (Global Descriptor Table) to
// fascilitate the transition to long-mode. We'll define that here

.global _tmp_gdt
.global _tmp_gdt_null
.global _tmp_gdt_code0
.global _tmp_gdt_data0
.global _tmp_gdt_code3
.global _tmp_gdt_data3
.global _tmp_gdt_tss
.global _tmp_gdt_end

.section .data
_tmp_gdt:
	.align 8 //The GDT should be aligned to 64-bits (8 bytes)
	
	// Basically, the GDT defines segments that the computer is permitted to
	// access. Since segment are deprecated in long (64-bit) mode, we just tell
	// the CPU to create two segments (one for code, one for data) that span the
	// ENTIRE address space. For future reference, each segment is 8 bytes in
	// size
	
	// We also define a null segment. It has to be there to conform to GDT
	// operation. We just set it to 0.
	
_tmp_gdt_null:
	.long 0
	.long 0
_tmp_gdt_code0:
	.word 0			// Limit [ 0:15]
	.word 0			// Base  [ 0:15]
	.byte 0			// Base  [16:23]
	.byte 0x98		// Present, DPL=0, Execute/Read, non-conforming
	.byte 0xA0		// Granularity, 32-bit, limit [16:19]
	.byte 0			// Base  [24:31]
_tmp_gdt_data0:
	.word 0			// Limit [ 0:15]
	.word 0			// Base  [ 0:15]
	.byte 0			// Base  [16:23]
	.byte 0x92		// Present, DPL=0, Read/Write
	.byte 0xCF		// limit [16:19] and attr
	.byte 0			// Base  [24:31]
_tmp_gdt_end:

// Next, we define a pointer to the GDT. This is important because it informs
// the CPU of the upper and lower bounds of the GDT (limit and base
// respectively). Notice how this is (word + double) in size (10 bytes). This is
// the value that will eventually be placed into the GDTR register to tell the
// CPU where the GDT is

_tmp_gdt_pointer:
	.word (. - _tmp_gdt - 1)	// Limit: Here we just grab the GDT's end label and subtract 1 (the limit defines the last byte of the GDT)
	.long _tmp_gdt				// Base: This one is obvious. It's just a pointer to the GDT

// We're assuming we're already in 32-bit protected mode.
.code32

// We're going to take this in several steps. No sense in rushing. The first
// step is to enter compatibility mode (a form of 64-bit that is
// backward-compatible with 32-bit protected mode)

.section .text
.global _enter_long_mode
_enter_long_mode:
	
	// Disable paging
	mov %cr0, %eax			// Move the cr0 (control) register into the accumulator
	and $(0x7FFFFFFF), %eax	// Set the PG (paging) bit (bit 31, FYI) to 0 in the accumulator
	mov %eax, %cr0			// Move the new accumulator value back into cr0
	
	// Set the PAE (Physical Address Extension) paging bit in cr4. This means we're enabling long addresses!
	mov %cr4, %eax			// Temporarily place the cr4 register into the accumulator
	bts $5, %eax			// Enable the PAE bit in the accumulator
	mov %eax, %cr4			// Place the new accumulator value back into the cr4 register
	
	// Set the IA32_EFER.LME (Long-Mode Enable) bit. 'EFER' Is the Extended
	// Feature Register. Another step towards fully entering long-mode
	mov $0xc0000080, %ecx	// Place the MSR address into the counter register
	rdmsr					// Load the contents of the 64-bit MSR into registers EDX:EAX. This is done because EDX & EAX are both 32-bit
	or $(1 << 8), %eax		// Set the 40th bit (the LME bit) (we use the 8th bit of EAX because the MSR is in EDX:EAX, which are both 32-bit)
	wrmsr					// Return the contents of registers EDX:EAX back into the 64-bit MSR
	
	// Construct the page tables. This is used for the shiny new long (64-bit)
	// mode paging system. We've already specified where this space is allocated
	jmp _construct_page_tables			// Now that the CR3 knows where the page tables are, we can construct them
	
	//Since we're jumping into a procedure (see line above) we need to have a label back into this one afterwards
	.global _enter_compatibility_page_table_return
	_enter_compatibility_page_table_return:
	
	// Re-enable paging ready for the JUMP TO LONG-MODE, CHEWIE!
	mov %cr0, %eax			// Temporarily place the 0th control register into the accumulator
	or $(1 << 31), %eax		// Enable the 31st bit (the paging bit) in the accumulator (set it to 1)
	mov %eax, %cr0			// Move the modified control-register value back into cr0 from the accumulator
	
	// Here's where we actually set the GDT. We don't set the GDTR manually, but
	// we have an instruction that does it for us (lgdt)
	lgdt _tmp_gdt_pointer
	
	// CHEWIE! HIT THE LONG-MODE DRIVE!
	pushl $0x8				// We're not actually using a proper far-jump here. We just define a segment base (pretty sure it can be anything)...
	pushl $_start64			// ...and then we push the location we want to jump to as well
	lret					//Then (bit of a hack) we simulate a far return with the data we just pushed
	//mov ($_tmp_gdt_code0), %eax
	//mov _start64, %ebx
	//ljmp %eax, %ebx
