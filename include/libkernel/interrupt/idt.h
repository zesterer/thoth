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

#ifndef LIBKERNEL_INTERRUPT_IDT_H
#define LIBKERNEL_INTERRUPT_IDT_H

// libthoth
#include "libthoth/type.h"

struct idt_entry __attribute__((packed))
{
	uint16 offset_low;
	uint16 selector;
	uint8 zero1;
	uint8 type_attributes;
	uint16 offset_mid;
	uint32 offset_high;
	uint32 zero2;
};

#endif
