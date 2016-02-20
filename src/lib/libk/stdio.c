#include "stdio.h"

#ifdef KERNEL_SPACE
	#include "../../kernel/thoth/vga.h"
#endif

/* Character input/output */

#ifdef KERNEL_SPACE
	int putchar(int character)
	{
		char char_str[2] = " ";
		char_str[0] = (char)character;
		thoth::puts(char_str);
	
		if (char_str[0] == character)
			return 1;
		return 0;
	}

	int puts(const char* str)
	{
		thoth::puts(str);
	
		return 0;
	}
#endif
