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
* Name:         idt.c
* 
* Description:  Interrupt Descriptor Table functions
* 
* Notes:        NONE
*/

// Local
#include "libkernel/interrupt/idt.h"

// libc
#include "libc/stdlib.h"
#include "libc/string.h"

// The default IDT
idt* idt_default = NULL;

idt* idt_setup_default()
{
	if (idt_default == NULL)
		idt_default = (idt*)malloc(sizeof(idt));
	
	for (sysint i = 0; i < sizeof(idt); i ++)
		((byte*)idt_get_default())[i] = 0;
	
	return idt_default;
}

void idt_set_current(idt* table)
{
	struct idtr { uint16 size; addr base; } __attribute__((packed));
	idtr current_idtr = {sizeof(idt), (void*)table};
	asm ("lidt %0" : : "m"(current_idtr));
}

idt* idt_get_default()
{
	return idt_default;
}

void idt_set_entry(idt* table, uint8 irq, interrupt_handler handler, uint16 selector, uint16 type_attributes)
{
	table->entries[irq].offset_low =  ((uint64)handler & 0x000000000000FFFF) >> 0;
	table->entries[irq].selector = selector;
	table->entries[irq].type_attributes = type_attributes;
	table->entries[irq].offset_mid =  ((uint64)handler & 0x00000000FFFF0000) >> 16;
	table->entries[irq].offset_high = ((uint64)handler & 0xFFFFFFFF00000000) >> 32;
	table->entries[irq].zero = 0;
}
