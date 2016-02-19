#include "vga.h"

#include "sys.h"

namespace thoth
{
	void vgaInit()
	{
		for (uint16 i = 0; i < VGA_WIDTH; i ++)
		{
			for (uint16 j = 0; j < VGA_HEIGHT; j ++)
			{
				VGA_BUFFER[j * VGA_WIDTH + i] = 0x0000;
				vgaSetFrontColor(i, j, VGAColor::VGA_WHITE);
			}
		}
	}
	
	void vgaSetCharacter(uint16 x, uint16 y, char character)
	{
		VGA_BUFFER[y * VGA_WIDTH + x] &= 0xFF00;
		VGA_BUFFER[y * VGA_WIDTH + x] |= (uint16)character;
	}
	
	void vgaSetBackColor(uint16 x, uint16 y, VGAColor color)
	{
		VGA_BUFFER[y * VGA_WIDTH + x] &= 0x0FFF;
		VGA_BUFFER[y * VGA_WIDTH + x] |= (uint16)(color << 12);
	}
	
	void vgaSetFrontColor(uint16 x, uint16 y, VGAColor color)
	{
		VGA_BUFFER[y * VGA_WIDTH + x] &= 0xF0FF;
		VGA_BUFFER[y * VGA_WIDTH + x] |= (uint16)(color << 8);
	}
	
	void vgaSetCursor(uint16 x, uint16 y)
	{
		uint16 pos = y * VGA_WIDTH + x;
		
		//Cursor LOW port
		outb(0x3D4, 0x0F);
		outb(0x3D5, (uint8)(pos & 0x00FF));
		//Cursor HIGH port
		outb(0x3D4, 0x0E);
		outb(0x3D5, (uint8)((pos >> 8) & 0x00FF));
	}
	
	void puts(const char* string, uint16 border)
	{
		if (string == nullptr)
			return;
		
		for (uint32 i = 0; string[i] != '\0'; i ++)
		{
			if (VGA_X >= VGA_WIDTH)
			{
				VGA_X = border;
				VGA_Y ++;
			}
			
			if (string[i] == '\n')
			{
				VGA_X = border;
				VGA_Y ++;
			}
			else
			{
				vgaSetCharacter(VGA_X, VGA_Y, string[i]);
				VGA_X ++;
			}
		}
		
		vgaSetCursor(VGA_X, VGA_Y);
	}
	
	void message(const char* string)
	{
		puts("         ");
		puts(string, 9);
	}
}
