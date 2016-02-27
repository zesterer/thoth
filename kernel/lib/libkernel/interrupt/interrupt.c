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
* Name:         interrupt.c
* 
* Description:  Interrupt functions
* 
* Notes:        NONE
*/

// Local
#include "libkernel/io/port.h"

void interrupt_set_enabled(bool enabled)
{
	if (enabled)
	{
		outb(0x21,0xfd);
		outb(0xa1,0xff);
		asm volatile ("sti");
	}
	else
		asm volatile ("cli");
}

bool interrupt_get_enabled()
{
	unsigned long flags;
	asm volatile ( "pushf\n\t"
	               "pop %0"
	             : "=g"(flags) );
	return flags & (1 << 9);
}
