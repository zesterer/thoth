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
#include "libkernel/vga/vgastream.h"
#include "libkernel/vga/vga.h"

// libc
#include "libc/stdlib.h"

// VGA stream variables
static int VGA_WIDTH = 80;
static int VGA_HEIGHT = 25;

// Global default stream
vga_stream vga_strm_default;
bool vga_strm_default_exists = false;

// Global functions
void vga_default_stream_init()
{
	vga_strm_default = vga_stream_create();
}

vga_stream* vga_get_default_stream()
{
	if (!vga_strm_default_exists)
	{
		vga_default_stream_init();
		vga_strm_default_exists = true;
	}
	
	return &vga_strm_default;
}

// VGA stream functions
vga_stream vga_stream_create()
{
	vga_stream strm;
	strm.init = vga_stream_init;
	strm.write_byte = vga_stream_write_byte;
	strm.write = vga_stream_write;
	
	strm.x = 0;
	strm.y = 0;
	
	strm.color_char = VGA_COLOR_WHITE;
	strm.color_back = VGA_COLOR_BLACK;
	
	strm.init((stream*)&strm);
	
	return strm;
}

void vga_buffer_clear(vga_stream* strm, uint16 value)
{
	for (int i = 0; i < VGA_WIDTH; i ++)
	{
		for (int j = 0; j < VGA_HEIGHT; j ++)
		{
			strm->buffer[j * VGA_WIDTH + i] = value;
		}
	}
}

void vga_buffer_to_vga(vga_stream* strm)
{
	for (int i = 0; i < VGA_WIDTH; i ++)
	{
		for (int j = 0; j < VGA_HEIGHT; j ++)
		{
			vga_set_value(i, j, strm->buffer[j * VGA_WIDTH + i]);
		}
	}
	
	vga_set_cursor_position(strm->x, strm->y);
}

void vga_buffer_scroll(vga_stream* strm, int amount)
{
	if (amount > 0)
	{
		for (int row = amount; row < VGA_HEIGHT; row ++)
		{
			for (int col = 0; col < VGA_WIDTH; col ++)
			{
				strm->buffer[(row - amount) * VGA_WIDTH + col] = strm->buffer[row * VGA_WIDTH + col];
				strm->buffer[row * VGA_WIDTH + col] = 0;
			}
		}
	}
}

void vga_stream_set_char(vga_stream* strm, int x, int y, uchar value)
{
	strm->buffer[y * VGA_WIDTH + x] &= 0xFF00;
	strm->buffer[y * VGA_WIDTH + x] |= (uint16)(value % 0x100);
}

void vga_stream_set_back_color(vga_stream* strm, int x, int y, uint color)
{
	strm->buffer[y * VGA_WIDTH + x] &= 0x0FFF;
	strm->buffer[y * VGA_WIDTH + x] |= (uint16)((color % 0x10) << 12);
}

void vga_stream_set_char_color(vga_stream* strm, int x, int y, uint color)
{
	strm->buffer[y * VGA_WIDTH + x] &= 0xF0FF;
	strm->buffer[y * VGA_WIDTH + x] |= ((color % 0x10) << 8);
}

void vga_stream_set_value(vga_stream* strm, int x, int y, uint16 value)
{
	strm->buffer[y * VGA_WIDTH + x] = value;
}

void vga_stream_init(stream* strm)
{
	vga_buffer_clear((vga_stream*)strm, 0x0F00);
}

void vga_stream_write_character(stream* strm, byte value)
{
	vga_stream* vga_strm = (vga_stream*)strm;
	char character = value % 0x100;
	bool output = true;
		
	switch (character)
	{
		case '\n':
			vga_strm->x = 0;
			vga_strm->y ++;
			output = false;
			break;
			
		case '\t':
			vga_strm->x ++;
			while (vga_strm->x % 4 != 0)
				vga_strm->x ++;
			output = false;
			break;
		
		case '\b':
			vga_strm->x --;
			if (vga_strm->x < 0 && vga_strm->y > 0)
			{
				vga_strm->y --;
				vga_strm->x = VGA_WIDTH - 1;
			}
			vga_stream_set_char(vga_strm, vga_strm->x, vga_strm->y, 0x0);
			vga_stream_set_char_color(vga_strm, vga_strm->x, vga_strm->y, vga_strm->color_char);
			vga_stream_set_back_color(vga_strm, vga_strm->x, vga_strm->y, vga_strm->color_back);
			output = false;
			break;
		
		default:
			break;
	}
	
	if (output)
	{
		vga_stream_set_char(vga_strm, vga_strm->x, vga_strm->y, character);
		vga_stream_set_char_color(vga_strm, vga_strm->x, vga_strm->y, vga_strm->color_char);
		vga_stream_set_back_color(vga_strm, vga_strm->x, vga_strm->y, vga_strm->color_back);
		vga_strm->x ++;
	}
	
	if (vga_strm->x >= VGA_WIDTH)
	{
		vga_strm->x = 0;
		vga_strm->y ++;
	}
	
	if (vga_strm->y >= VGA_HEIGHT)
	{
		vga_buffer_scroll(vga_strm, vga_strm->y - VGA_HEIGHT + 1);
		vga_strm->y = VGA_HEIGHT - 1;
	}
}

void vga_stream_write_byte(stream* strm, byte value)
{
	vga_stream_write_character(strm, value);
	
	// Buffer the result to the VGA device
	vga_buffer_to_vga((vga_stream*)strm);
}

void vga_stream_write(stream* strm, const byte* data, sysint size)
{
	vga_stream* vga_strm = (vga_stream*)strm;
	
	for (uint i = 0; i < size; i ++)
	{
		bool output = true;
		
		switch (data[i])
		{
			case '\\': // Escape code
				if (i >= size - 1) //Check we're not at the end of the string
					break;
				
				switch (data[i + 1])
				{
					case 'C': // The character color escape code
						if (i >= size - 2) // Check to make sure there's the color definition on the end
							break;
						
						output = false;
						
						if (data[i + 2] >= '0' && data[i + 2] <= '9')
							vga_strm->color_char = data[i + 2] - '0';
						if (data[i + 2] >= 'A' && data[i + 2] <= 'F')
							vga_strm->color_char = data[i + 2] - 'A' + 10;
						
						i += 2;
						break;
						
					case 'B': // The character color escape code
						if (i >= size - 2) // Check to make sure there's the color definition on the end
							break;
						
						output = false;
						
						if (data[i + 2] >= '0' && data[i + 2] <= '9')
							vga_strm->color_back = data[i + 2] - '0';
						if (data[i + 2] >= 'A' && data[i + 2] <= 'F')
							vga_strm->color_back = data[i + 2] - 'A' + 10;
						
						i += 2;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
			
		if (output)
			vga_stream_write_character(strm, data[i]);
	}
	
	// Buffer the result to the VGA device
	vga_buffer_to_vga(vga_strm);
}
