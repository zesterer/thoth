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
* Name:         string.c
* 
* Description:  C standard library string & memory manipulation functions
* 
* Notes:        NONE
*/

// Local
#include "libc/string.h"

// Standard GCC header
#include "stdint.h"

// libthoth
#include "libthoth/type.h"

/* Copying */

void* memcpy(void* destination, const void* source, size_t num)
{
	for (size_t i = 0; i < num; i ++)
		((unsigned char*)destination)[i] = ((unsigned char*)source)[i];
	
	return destination;
}

char* strcpy(char* destination, const char* source)
{
	for (size_t i = 0; source[i] != '\0'; i ++)
		destination[i] = source[i];
	
	return destination;
}

char* strncpy(char* destination, const char* source, size_t num)
{
	for (size_t i = 0; i < num && source[i] != '\0'; i ++)
		destination[i] = source[i];
	
	return destination;
}

//Concatenation
char* strcat(char* destination, const char* source)
{
	size_t len = strlen(destination);
	
	for (size_t i = 0; source[i] != '\0'; i ++)
		destination[i + len] = source[i];
	
	return destination;
}

/* Comparasion */

int strcmp(const char* str1, const char* str2)
{
	int i = 0;
	
	while (str1[i] == str2[i])
	{
		if (str2[i++] == 0)
			return 0;
	}
	
	return 1;
}

int strncmp(const char* str1, const char* str2, size_t num)
{
	int result = 0;
	
	while (num)
	{
		result = *str1 - *str2++;
		
		if (result != 0 || *str1++ == 0)
			break;
		
		num--;
	}
	
	return result;
}

/* Searching */

void* memchr(void* ptr, int value, size_t num)
{
	for (size_t i = 0; i < num; i ++)
	{
		if (((byte*)ptr)[i] == (uchar)value)
			return &((byte*)ptr)[i];
	}
	
	return NULL;
}

/* Other */
void* memset(void* ptr, int value, size_t num)
{
	for (size_t i = 0; i < num; i ++)
		((unsigned char*)ptr)[i] = (unsigned char)value;
	
	return ptr;
}

size_t strlen(const char* str)
{
	size_t i;
	for (i = 0; str[i] != '\0'; i ++) {}
	return i;
}
