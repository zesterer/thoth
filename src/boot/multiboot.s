// The operating system must be prefixed with a multiboot header. This tells
// GRUB that we are a bootable operating system. It has a unique signature to
// prevent misidentification

// Here, we define some constants that'll be used in the multiboot header

.SET MULTIBOOT_MAGIC, 0x1BADB002								// The magic identifier that GRUB sees
.SET MULTIBOOT_FLAGS, (1 << 0 | 1 << 1)							// Multiboot header flags
.SET MULTIBOOT_CHECKSUM, -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)	//The checksum to verify that the header is valid

// We put the header in it's own section such that we can force it to be at the
// beginning of the kernel code

.section .multiboot
	
	.align 4	// Align this section to 32 bits

_multiboot_header:				// Just a label to direct us
	
	.long MULTIBOOT_MAGIC		// Place the multiboot identifier in the header
	.long MULTIBOOT_FLAGS		//	Place the flags in the header
	.long MULTIBOOT_CHECKSUM	//	Place the checksum in the header
	
	// I'm not massively sure about about the following bit, but apparently it's
	// an important component of a valid multiboot header
	
	.long _multiboot_header
	.long 0						// Will eventually be kernel_text_start
	.long 0						// Will eventually be kernel_data_end
	.long 0						// Will eventually be kernel_bss_end
