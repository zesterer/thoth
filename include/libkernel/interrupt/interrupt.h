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
* Name:         interrupt.h
* 
* Description:  Interrupt functions
* 
* Notes:        NONE
*/

#ifndef LIBKERNEL_INTERRUPT_INTERRUPT_H
#define LIBKERNEL_INTERRUPT_INTERRUPT_H

// Libthoth
#include "libthoth/type.h"

typedef void (*interrupt_handler)(int irq);

void interrupt_set_enabled(bool enabled);
bool interrupt_get_enabled();

/*static inline void interrupt_handle()
{
	asm volatile("mov $20, %al\n"
	"out %al, $20");
}*/

void interrupt_set_handler(void* handler);

#endif
