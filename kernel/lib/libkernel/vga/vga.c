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
* Name:         vga.c
* 
* Description:  Utilities to interface with a system's VGA device
* 
* Notes:        NONE
*/

// Local
#include "libkernel/vga/vga.h"
#include "libkernel/io/port.h"

// Locally used variables
static uint VGA_WIDTH = 80;
static uint VGA_HEIGHT = 25;
static uint VGA_CURSOR_X = 0;
static uint VGA_CURSOR_Y = 0;
static uint16* VGA_MEMORY = (uint16*)0xB8000;

void vga_clear(uint16 value)
{
	for (uint i = 0; i < VGA_WIDTH; i ++)
	{
		for (uint j = 0; j < VGA_HEIGHT; j ++)
		{
			VGA_MEMORY[j * VGA_WIDTH + i] = value;
		}
	}
}

void vga_set_char(uint x, uint y, uchar value)
{
	VGA_MEMORY[y * VGA_WIDTH + x] &= 0xFF00;
	VGA_MEMORY[y * VGA_WIDTH + x] |= (uint16)(value % 0x100);
}

void vga_set_back_color(uint x, uint y, uint color)
{
	VGA_MEMORY[y * VGA_WIDTH + x] &= 0x0FFF;
	VGA_MEMORY[y * VGA_WIDTH + x] |= (uint16)((color % 0x10) << 12);
}

void vga_set_char_color(uint x, uint y, uint color)
{
	VGA_MEMORY[y * VGA_WIDTH + x] &= 0xF0FF;
	VGA_MEMORY[y * VGA_WIDTH + x] |= (uint16)((color % 0x10) << 8);
}

void vga_set_value(uint x, uint y, uint16 value)
{
	VGA_MEMORY[y * VGA_WIDTH + x] = value;
}

uchar vga_get_char(uint x, uint y)
{
	return VGA_MEMORY[y * VGA_WIDTH + x] & 0x00FF;
}

uint  vga_get_char_color(uint x, uint y)
{
	return (VGA_MEMORY[y * VGA_WIDTH + x] & 0x0F00) >> 8;
}

uint  vga_get_back_color(uint x, uint y)
{
	return (VGA_MEMORY[y * VGA_WIDTH + x] & 0xF000) >> 12;
}

// Set and get the VGA device's cursor position
void vga_set_cursor_position(uint x, uint  y)
{
	uint16 pos = y * VGA_WIDTH + x;
	
	//Cursor LOW port
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8)(pos & 0x00FF));
	//Cursor HIGH port
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8)((pos >> 8) & 0x00FF));
}

void vga_get_cursor_position(uint* x, uint* y)
{
	*x = VGA_CURSOR_X;
	*y = VGA_CURSOR_Y;
}
