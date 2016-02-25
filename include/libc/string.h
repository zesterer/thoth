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
* Name:         string.h
* 
* Description:  C standard library string & memory manipulation functions
* 
* Notes:        NONE
*/

#ifndef LIBC_STRING_H
#define LIBC_STRING_H

// Standard GCC header
#include "stddef.h"

//Copying
void* memcpy(void* destination, const void* source, size_t num);
void* memmove(void* destination, const void* source, size_t num);
char* strcpy(char* destination, const char* source);
char* strncpy(char* destination, const char* source, size_t num);

//Concatenation
char* strcat(char* destination, const char* source);
char* strncat(char* destination, const char* source, size_t num);

//Comparasion
int memcmp(const void* ptr1, const void* ptr2, size_t num);
int strcmp(const char* str1, const char* str2);
int strcoll(const char* str1, const char* str2);
int strncmp(const char* str1, const char* str2, size_t num);
size_t strxfrm(char* destination, const char* source, size_t num);

//Searching
void* memchr(void* ptr, int value, size_t num);

//Other
void* memset(void* ptr, int value, size_t num);
size_t strlen(const char* str);

#endif
