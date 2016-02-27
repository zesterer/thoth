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
* Name:         boot.s
* 
* Description:  x86_64 pre-kernel boot code
* 
* Notes:        NONE
*/

// Currently the stack pointer register (esp) points at anything and using it may
// cause massive harm. Instead, we'll provide our own stack. We will allocate
// room for a small temporary stack by creating a symbol at the bottom of it,
// then allocating 16384 bytes for it, and finally creating a symbol at the top.

// This stack is being allocated a small region of 16 kilobytes. Once we have a
// C environment running and we've entered long (64-bit) mode, we can define a
// proper stack for the kernel. But for now, this temporary structure will
// be sufficient until such a time where we can get a stable long (64-bit) mode
// environment set up

//NOTE: On the x86 architecture, the stack grows DOWNWARD.

// The @nobits directive specifies that this region should contain empty space only
.section .bootstrap_stack, "aw", @nobits
	_stack_bottom:				//Add a label for the bottom of the stack
	.skip 65536					//Define 64 KiB of memory for the stack
	_stack_top:					//Add a label for the top of the stack

// We're writing this code in 32-bit protected mode for now
.code32

// .section .text basically just says that this is read-only memory from now on
.section .text

// The linker script specifies _bootstrap as the entry point to the kernel and the
// bootloader will jump to this position once the kernel has been loaded. It
// doesn't make sense to return from this function as the bootloader is gone.

// The 32-bit bootstrap procedure
.global _bootstrap
.type _bootstrap, @function
_bootstrap:
	
	// Disable interrupts
	cli
	
	// Set the stack pointer to the top of the temporary stack
	movl $(_stack_top), %esp
	
	// Clear EBP and EFLAGS
	mov $0, %ebp
	pushl 0
	popl %eax

	//Display 'Booting' on the screen to show that we're actually booting
	mov $(0xB8000 + 0x0), %eax
	movb $66, (%eax)
	mov $(0xB8000 + 0x2), %eax
	movb $111, (%eax)
	mov $(0xB8000 + 0x4), %eax
	movb $111, (%eax)
	mov $(0xB8000 + 0x6), %eax
	movb $116, (%eax)
	mov $(0xB8000 + 0x8), %eax
	movb $105, (%eax)
	mov $(0xB8000 + 0xA), %eax
	movb $110, (%eax)
	mov $(0xB8000 + 0xC), %eax
	movb $103, (%eax)
	//jmp _hang_cpu
	
	// Set up long (64-bit) mode
	jmp _enter_long_mode

// Define a CPU hang procedure (Useful if we want to put the CPU to sleep)
.global _hang_cpu
_hang_cpu:							//A hang procedure just in case the CPU ever wakes up for some reason
	jmp _hang_cpu					//Jump back into the procedure (i.e: an infinite loop)

// Long (64-bit) mode code from now on!
.code64

// The long (64-bit) mode bootstrap
.global _start64
_start64:
	
	// Here's the bit where we'd usually assign the page segments if we were
	// using standard old x86. Instead, we're just bunging our segments in that
	// tell the CPU it's allowed to access the entire address space (proper
	// address partition is done with the paging system)
	
	// Grab the GDT and ram it into all the segment registers (although this should be ignored)
	//mov $(_tmp_gdt_data0), %rax
	//mov %rax, %ds				// Set ALL the segment registers
	//mov %rax, %es				// Set ALL the segment registers
	//mov %rax, %fs				// Set ALL the segment registers
	//mov %rax, %gs				// Set ALL the segment registers
	//mov %rax, %ss				// Set ALL the segment registers
	
	// Welcome to kernel mode! We now have sufficient code for the bootloader to
	// load and run the operating system. It doesn't do anything interesting yet.
	// Perhaps we would like to call printf("Hello, World\n"). You should now
	// realize one of the profound truths about kernel mode: There is nothing
	// there unless you provide it yourself. There is no printf function. There
	// is no <stdio.h> header. If you want a function, you will have to code it
	// yourself. And that is one of the best things about kernel development:
	// you get to make the entire system yourself. You have absolute and complete
	// power over the machine, there are no security restrictions, no safe
	// guards, no debugging mechanisms, there is nothing but what you build.
	
	// Setup the 64-bit stack pointer
	mov $(_stack_top), %rsp
	
	// We are now ready to actually execute C code. We cannot embed that in an
	// assembly file, so we'll create a kernel.c file in a moment. In that file,
	// we'll create a C entry point called kernelMain and call it here.
	
	call kernel_start			// Enter the kernel_start function (C)
	
	// In case the function returns, we'll want to put the computer into an
	// infinite loop. To do that, we use the clear interrupt ('cli') instruction
	// to disable interrupts, the halt instruction ('hlt') to stop the CPU until
	// the next interrupt arrives, and jumping to the halt instruction if it ever
	// continues execution, just to be safe. We will create a local label rather
	// than real symbol and jump to there endlessly.
	
	cli							// Disable interrupts
	hlt							// Halt the CPU
	
	jmp _hang_cpu					//Just in case

.section .end_of_kernel
.global _end_of_kernel
_end_of_kernel:
