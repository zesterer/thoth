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
* Name:         vga.h
* 
* Description:  Utilities to interface with a system's VGA device
* 
* Notes:        NONE
*/

#ifndef LIBKERNEL_VGA_VGA_H
#define LIBKERNEL_VGA_VGA_H

// Local
#include "libthoth/type.h"

// VGA color constants
enum
{
	VGA_COLOR_BLACK         = 0,
	VGA_COLOR_BLUE          = 1,
	VGA_COLOR_GREEN         = 2,
	VGA_COLOR_CYAN          = 3,
	VGA_COLOR_RED           = 4,
	VGA_COLOR_MAGENTA       = 5,
	VGA_COLOR_BROWN         = 6,
	VGA_COLOR_LIGHT_GREY    = 7,
	VGA_COLOR_DARK_GREY     = 8,
	VGA_COLOR_LIGHT_BLUE    = 9,
	VGA_COLOR_LIGHT_GREEN   = 10,
	VGA_COLOR_LIGHT_CYAN    = 11,
	VGA_COLOR_LIGHT_RED     = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN   = 14,
	VGA_COLOR_WHITE         = 15,
};

// Clear the VGA device with a value
void vga_clear(uint16 value);

// Set cell-specific VGA properties
void vga_set_char      (uint x, uint y, uchar  value);
void vga_set_char_color(uint x, uint y, uint   color);
void vga_set_back_color(uint x, uint y, uint   color);
void vga_set_value     (uint x, uint y, uint16 value);

// Get cell-specific VGA properties
uchar vga_get_char      (uint x, uint y);
uint  vga_get_char_color(uint x, uint y);
uint  vga_get_back_color(uint x, uint y);

// Set and get the VGA device's cursor position
void vga_set_cursor_position(uint  x, uint  y);
void vga_get_cursor_position(uint* x, uint* y);

#endif
