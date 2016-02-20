#include "stdio.h"

#include "../../kernel/thoth/vga.h"

/* Character input/output */

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
