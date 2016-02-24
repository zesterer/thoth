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
* Name:         vga.c
* 
* Description:  Utilities to interface with a system's VGA device
* 
* Notes:        NONE
*/

// Local
#include "libc/stdio.h"
#include "libc/string.h"

// libkernel
#include "libkernel/vga/vgastream.h"

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
	size_t len = strlen(format);
	
	vga_get_default_stream()->write((stream*)vga_get_default_stream(), (byte*)format, len);
	
	return len;
}
