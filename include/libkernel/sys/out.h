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
* Name:         out.h
* 
* Description:  Functions to output to I/O ports
* 
* Notes:        NONE
*/

#ifndef LIBTHOTH_STREAM_STREAM_H
#define LIBTHOTH_STREAM_STREAM_H

// Local
#include "libthoth/type.h"

// Output functions
static inline void outb(uint16 port, uint8 value)
{
	asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
	/* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
	* Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
	* The  outb  %al, %dx  encoding is the only option for all other cases.
	* %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

static inline void outw(uint16 port, uint16 value)
{
	asm volatile("outw %0, %1" : : "a"(value), "Nd"(port));
}

static inline void outl(uint16 port, uint32 value)
{
	asm volatile("outl %0, %1" : : "a"(value), "Nd"(port));
}

#endif
