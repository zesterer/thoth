#include "libc/stdio.h"
#include "libc/string.h"

#ifdef KERNEL_SPACE
	#include "libthoth/vga.h"
#endif

/* Character input/output */

#ifdef KERNEL_SPACE
	int putchar(int character)
	{
		thoth::vgaPutChar((char)character);
	
		if ((char)character == character)
			return 1;
		return 0;
	}

	int puts(const char* str)
	{
		thoth::vgaPuts(str);
	
		return 0;
	}
	
	int printf(const char* format, ...)
	{
		thoth::vgaPrintf(format);
		
		return strlen(format);
	}
#endif
