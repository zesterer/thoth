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
* Name:         stdio.c
* 
* Description:  C standard library input / output functions
* 
* Notes:        NONE
*/

// Local
#include "libc/stdio.h"
#include "libc/string.h"
#include "libc/stdlib.h"
#include "libc/ctype.h"

// libkernel
#include "libkernel/vga/vgastream.h"

// GCC standard header
#include "stdarg.h"

/* Character input/output */

int putchar(int character)
{
	vga_get_default_stream()->write_byte((stream*)vga_get_default_stream(), (char)character);

	if ((char)character == character)
		return 1;
	return 0;
}

int puts(const char* str)
{
	size_t len = strlen(str);
	
	vga_get_default_stream()->write((stream*)vga_get_default_stream(), (byte*)str, len);

	return 0;
}

int printf(const char* format, ...)
{
	stream* strm = (stream*)vga_get_default_stream();
	
	size_t len = 0;
	size_t format_len = strlen(format);
	
	va_list args;
	va_start(args, format);
	
	size_t last = 0;
	size_t i;
	for (i = 0; i < format_len; i ++)
	{
		switch (format[i])
		{
			case '%':
			{
				if (i >= format_len - 1) // Make sure we're not at the end of the string
					break;
				
				switch (format[i + 1])
				{
					case 'c': // We're writing a string
					{
						strm->write(strm, (byte*)&(format[last]), i - last); // Write the string so far
						// Write the string we found in the gap
						char* str = va_arg(args, char*);
						strm->write(strm, (byte*)str, strlen(str)); // Write the inserted string
						last = i + 2; // The string format sequence was 2 characters long
						break;
					}
					case 'd': // We're writing a signed int
					case 'i':
					case 'x': // We're writing a hexadecimal int
					case 'X':
					case 'u': // We're writing an unsigned int
					case 'o': // We're writing an octal int
					{
						strm->write(strm, (byte*)&(format[last]), i - last); // Write the string so far
						
						// Write the string we found in the gap
						char str[sizeof(int) * 8 + 1]; // This string is the maximum size an int could possibly be
						
						int v = va_arg(args, int);
						
						if (format[i + 1] == 'u') // Is it unsigned?
							v = abs(v);
						
						int base = (format[i + 1] == 'x' || format[i + 1] == 'X') ? 16 : ((format[i + 1] == 'o') ? 8 : 10); // Which base are we using?
						itoa(v, str, base); // Convert it to a string
						
						if (format[i + 1] == 'x') // Convert it to uppercase if we have to
						{
							for (int i = 0; str[i] != '\0'; i ++)
								str[i] = tolower(str[i]);
						}
						
						strm->write(strm, (byte*)str, strlen(str)); // Write the inserted string
						last = i + 2; // The string format sequence was 2 characters long
						break;
					}
					default:
						break;
				}
			}
			default:
				break;
		}
		
		len ++;
	}
	strm->write(strm, (byte*)&(format[last]), i - last); // Write any trailing string
	
	va_end(args);
	
	return len;
}
