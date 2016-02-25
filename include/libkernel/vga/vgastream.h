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
* Name:         vgastream.h
* 
* Description:  A stream interface to the VGA console
* 
* Notes:        NONE
*/

#ifndef LIBKERNEL_VGA_VGASTREAM_H
#define LIBKERNEL_VGA_VGASTREAM_H

// Local
#include "libthoth/type.h"
#include "libthoth/stream/stream.h"

// VGA stream definition
struct vga_stream;

// Global functions
void vga_default_stream_init();
vga_stream* vga_get_default_stream();

// Stream generic functions
vga_stream vga_stream_create();
void vga_stream_init(stream* strm);
void vga_stream_write_byte(stream* strm, byte value);
void vga_stream_write(stream* strm, const byte* data, sysint size);

// VGA stream functions
void vga_stream_set_char      (vga_stream* strm, uint x, uint y, uchar  value);
void vga_stream_set_char_color(vga_stream* strm, uint x, uint y, uint   color);
void vga_stream_set_back_color(vga_stream* strm, uint x, uint y, uint   color);
void vga_stream_set_value(vga_stream* strm, uint x, uint y, uint16 value);

// VGA stream implementation
struct vga_stream
{	
	fptr_stream_init init;
	fptr_stream_write_byte write_byte;
	fptr_stream_write write;
	
	// Put other data AFTERWARDS (so that if code treats it as an ordinary stream it still runs the functions)
	uint x, y;
	uint16 buffer[80 * 25];
	byte color_char, color_back;
};

#endif
