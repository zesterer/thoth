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
* Name:         paging.s
* 
* Description:  x86_64 pre-kernel boot code
* 
* Notes:        NONE
*/

// This code is used to set up paging. This is obviously a long (64-bit) mode
// only feature, so this code *should* be executed as part of the
// _enter_long_mode procedure.

// Here we allocate enough space to make some page tables. We place them inside
// the .bss because that has read/write permissions (and we'll need this for the
// page tables). We'll use 24 Kb of memory. This is enough for 4GB of pages. If
// that's not enough memory to do whatever the heck we want for now, I don't
// know what is.

// How paging works:
// 
//    PML4             PDP              PD           Physical Mem
//  ________         ________         ________         ________
// |________|       |________|       |________|       |________|
// |________| ----> |________|       |________|       |________|
// |________|       |________|       |________| ----> |________|
// |________|       |________| ----> |________|       |________|
// |________|       |________|       |________|       |________|
// |________|       |________|       |________|       |________|
// 
// Since we're using 2MB pages...
// ...We're creating 1 PML4 entry
// ...We're creating 1x4 PDP entries
// ...We're creating 1x4x512 PD entries
// ...And so we're mapping 1x4x512x2MB = 4GB of physical memory

.section .bss
	.align 0x1000		// Align to 4KB (4096 bytes)

.global _page_map_level_4_top
_page_map_level_4_top:		// A label to tell us where the top is
	.skip 0x6000			// Here we reserve enough bytes to store 24 KB worth of page tables
.global _page_map_level_4_bottom
_page_map_level_4_bottom:	// A label to tell us where the bottom is

// Now we're going to define a procedure that'll properly create our 24KB page
// table structure. It'll be called by the compatibility entry procedure

.section .text
	.global _construct_page_tables		// Make the _construct_page_tables procedure globally accessable

// We're STILL in 32-bit protected mode at the moment, so specify this
.code32

_construct_page_tables:		// A label so we can access this procedure from elsewhere
	
	// First, we should set about clearing the 24KB of page table space. This
	// *should* be already done, but since we can't guarantee this, we're going
	// to clear it anyway.
	
	/* CLEAR PAGING TABLES */
	
	mov $(_page_map_level_4_top), %edi	// Put the PML4 pointer temporarily into a general-purpose register
	mov %edi, %cr3					// Tell CR3 where the page tables are located
	xor %eax, %eax					// Zero the accumulator just in case it wasn't already zero
	mov $0x6000, %ecx				// Move 0x6000 (24KB) into the counter register
	rep								// Repeatedly copy the value in the accumulator (0) into memory, as per the number of times in the counter (6KB)
	//stosd							// Copy EAX to EDI (Why? Not sure)
	mov %cr3, %edi					// Copy CR3 into EDI
	
	/* FILL PML4 */
	
	// Create a PML4 entry (PML4E)
	movl $0x1007, (%edi)				// Read/write and user-space permissions (note: 0x7 = 0b111) and 4KB offset. Presumably because this memory is aligned with 4KB anyway, any smaller value here is treated as data about permissions. Yes, it's confusing
	addl $(_page_map_level_4_top), (%edi)	// Points to PML4 + 4KB (specified on line above ^)
	
	add $0x1000, %edi					// Now increment EDIto PML4 location + 4KB (The PDP Table)
	
	/* FILL PDP */
	
	// Now we're creating 4 Page Directory Pointer Entries (PDPE)
	movl $0x2007, (%edi)		// Present, read/write permissions, user-space
	addl $(_page_map_level_4_top), (%edi)	// Points to PML4 + 8KB
	add $8, %edi //Increment to the next PDPE (we're making a table after all...)
	
	movl $0x3007, (%edi)		// Present, read/write permissions, user-space
	addl $(_page_map_level_4_top), (%edi)	// Points to PML4 + 12KB
	add $8, %edi //Increment to the next PDPE
	
	movl $0x4007, (%edi)		// Present, read/write permissions, user-space
	addl $(_page_map_level_4_top), (%edi)	// Points to PML4 + 16KB
	add $8, %edi //Increment to the next PDPE
	
	movl $0x5007, (%edi)		// Present, read/write permissions, user-space
	addl $(_page_map_level_4_top), (%edi)	// Points to PML4 + 20KB
	// We don't need to increment this one... We're at the end of this PDP!
	
	add $(0x1000 - 24), %edi //Increment to the Page Directory (PD) (not PDPE, hence the bigger jump. We have to go backwards 24 bytes though, since we just incremented by that many (see the crap above))
	
	// Here we go! The last part of page table construction. This is the weird
	// part because we're looping. Keep all limbs within the vehicle, grab hold
	// of your hair and kiss your sanity goodbye
	
	/* FILL PD */
	
	// Create 4 * 512 Page Directory Entries (PDE)
	mov $0x00000087, %ebx		// Present, read/write, 2MB granularity (i.e: Each page is 2MB)
	mov $(4 * 512), %ecx		// We are making 4 * 512 entries after all...

_set_pdp_entry:					// This is our little loop label
	movl %ebx, (%edi)			// Move EBX (i.e: the permissions we're currently talking about) into the correct location
	add $(1 << 21), %ebx		// Increment by 0x200000 (2MB). So basically skip to the next page location
	add $8, %edi				// Increment! We're done with this entry, go to the next one.
	loop _set_pdp_entry			// Loop until the counter is 0
	
	// Return back to the previous procedure
	jmp _enter_compatibility_page_table_return
