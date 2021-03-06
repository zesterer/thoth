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
* Name:         stdio.h
* 
* Description:  C standard library input / output functions
* 
* Notes:        NONE
*/

#ifndef LIBC_STDIO_H
#define LIBC_STDIO_H

//Macros
#define EOF -1

//Operations on files
//TODO

//File access
//TODO

//Formatted input/output
int printf(const char* format, ...);
//TODO - complete this

//Character input/output
int putchar(int character);
int puts(const char* str);
//TODO - complete this

//Direct input/output
//TODO

//File positioning
//TODO

//Error-handling
//TODO

#endif
