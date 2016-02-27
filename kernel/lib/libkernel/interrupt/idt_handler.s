// Assembly interrupt handler

.code64
.global isr_handler
.global interrupt_handler_address

.section .text
.align 4

.macro save_regs
	push %rax
	push %rbx
	push %rcx
	push %rdx
	push %rdi
	push %rsi
	push %rbp
	push %r8
	push %r9
	push %r10
	push %r11
	push %r12
	push %r13
	push %r14
	push %r15
.endm
	
.macro restore_regs
	pop %r15
	pop %r14
	pop	%r13
	pop	%r12
	pop	%r11
	pop	%r10
	pop	%r9
	pop	%r8
	pop	%rbp
	pop	%rsi
	pop	%rdi
	pop	%rdx
	pop	%rcx
	pop	%rbx
	pop	%rax
.endm

isr_handler:
	save_regs		// Push general-purpose registers onto the stack
	cld				// Clear the direction flag
	mov (interrupt_handler_address), %rdx	// Select the interrupt service routine
	call *%rdx		// Actually call the interrupt service routine
	restore_regs	// Pop general-purpose registers onto the stack
	jmp _kernel_panic
	iretq			// Return from the interrupt

.section .data
interrupt_handler_address:	.long 0
