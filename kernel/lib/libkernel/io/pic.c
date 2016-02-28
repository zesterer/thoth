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
* Name:         pic.c
* 
* Description:  Functions to manage the PIC (Programmable Interrupt Controller)
* 
* Notes:        NONE
*/

// Local
#include "libkernel/io/pic.h"
#include "libkernel/io/port.h"

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

#define PIC_EOI		0x20		/* End-of-interrupt command code */


#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

void pic_init(byte offset0, byte offset1)
{
	byte a0 = inb(PIC1_DATA);
	byte a1 = inb(PIC2_DATA);
	
	// IO_WAIT is used after every port command to assure that the PIC received it
	
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); // Start initialization of the master
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4); // Start initialization of the slave
	io_wait();
	
	outb(PIC1_DATA, offset0); // Master PIC offset vector
	io_wait();
	outb(PIC2_DATA, offset1); // Slave PIC offset vector
	io_wait();
	
	outb(PIC1_DATA, 0x4); // Tell the master that a slave exists at IRQ2
	io_wait();
	outb(PIC2_DATA, 0x2); // Tell the slave it's cascade identity
	io_wait();
	
	outb(PIC1_DATA, ICW4_8086); // Set the master's mode to 8086
	io_wait();
	outb(PIC2_DATA, ICW4_8086); // Set the slave's mode to 8086
	io_wait();
	
	outb(PIC1_DATA, a0); // Restore saved master masks
	outb(PIC2_DATA, a1); // Restore saved slaver masks
	
	// Testing
	for (int i = 0; i < 255; i ++)
		pic_set_mask(i);
	pic_clear_mask(1);
}

void pic_end_interrupt(byte irq)
{
	if (irq >= 8)
		outb(PIC2, PIC_EOI);
	outb(PIC1, PIC_EOI);
}

void pic_set_mask(byte line)
{
	uint16_t port;
	uint8_t value;
	
	if(line < 8)
	{
		port = PIC1_DATA;
	}
	else
	{
		port = PIC2_DATA;
		line -= 8;
	}
	value = inb(port) | (1 << line);
	outb(port, value);        
}

void pic_clear_mask(byte line)
{
	uint16_t port;
	uint8_t value;
	
	if(line < 8)
	{
		port = PIC1_DATA;
	}
	else
	{
		port = PIC2_DATA;
		line -= 8;
	}
	value = inb(port) & ~(1 << line);
	outb(port, value);        
}
