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
* Name:         port.h
* 
* Description:  Functions to read/write to I/O ports
* 
* Notes:        NONE
*/

#ifndef LIBKERNEL_IO_PORT_H
#define LIBKERNEL_IO_PORT_H

// Libthoth
#include "libthoth/type.h"

static inline void io_wait(void)
{
	asm volatile ( "jmp 1f\n\t"
	               "1:jmp 2f\n\t"
	               "2:" );
}

static inline void outb(uint16 port, uint8  value)
{
	asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline void outw(uint16 port, uint16 value)
{
	asm volatile ("outw %0, %1" : : "a"(value), "Nd"(port));
}

static inline void outl(uint16 port, uint32 value)
{
	asm volatile ("outl %0, %1" : : "a"(value), "Nd"(port));
}

static inline void outq(uint16 port, uint64 value)
{
	asm volatile ("outq %0, %1" : : "a"(value), "Nd"(port));
}

static inline uint8 inb(uint16 port)
{
	uint8 value;
	asm volatile ("inb %[port], %[ret]"
	              : [ret] "=a"(value)
	              : [port] "Nd"(port));
	return value;
}

static inline uint16 inw(uint16 port)
{
	uint16 value;
	asm volatile ("inw %[port], %[ret]"
	              : [ret] "=a"(value)
	              : [port] "Nd"(port));
	return value;
}

static inline uint32 inl(uint16 port)
{
	uint32 value;
	asm volatile ("inl %[port], %[ret]"
	              : [ret] "=a"(value)
	              : [port] "Nd"(port));
	return value;
}

#endif
