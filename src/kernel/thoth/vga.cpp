#include "vga.h"

#include "sys.h"
#include "string.h"

namespace thoth
{
	static uint16 VGA_WIDTH = 80;
	static uint16 VGA_HEIGHT = 25;
	
	static uint16* VGA_LOCATION = (uint16*)0xB8000;
	static uint16 VGA_BUFFER[80 * 25];
	
	static uint16 VGA_X = 0;
	static uint16 VGA_Y = 0;
	
	static VGAColor VGA_BACK_COL = VGA_BLACK;
	static VGAColor VGA_FRONT_COL = VGA_WHITE;
	
	
	
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
	
	void vgaUpdate()
	{
		for (uint16 i = 0; i < VGA_WIDTH; i ++)
		{
			for (uint16 j = 0; j < VGA_HEIGHT; j ++)
			{
				VGA_LOCATION[j * VGA_WIDTH + i] = VGA_BUFFER[j * VGA_WIDTH + i];
			}
		}
	}
	
	void vgaScroll(int16 amount)
	{
		if (amount > 0)
		{
			for (int16 row = amount; row < VGA_HEIGHT; row ++)
			{
				for (int16 col = 0; col < VGA_WIDTH; col ++)
					VGA_BUFFER[(row - amount) * VGA_WIDTH + col] = VGA_BUFFER[row * VGA_WIDTH + col];
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
	
	void vgaSetValue(uint16 x, uint16 y, uint16 value)
	{
		VGA_BUFFER[y * VGA_WIDTH + x] = value;
	}
	
	uint16 vgaGetValue(uint16 x, uint16 y)
	{
		return VGA_BUFFER[y * VGA_WIDTH + x];
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
	
	void vgaPutChar(char character)
	{
		bool output = true;
		
		switch (character)
		{
			case '\n':
				VGA_X = 0;
				VGA_Y ++;
				output = false;
				break;
			
			default:
				break;
		}
		
		if (output)
		{
			vgaSetCharacter(VGA_X, VGA_Y, character);
			vgaSetBackColor(VGA_X, VGA_Y, VGA_BACK_COL);
			vgaSetFrontColor(VGA_X, VGA_Y, VGA_FRONT_COL);
			VGA_X ++;
		}
		
		if (VGA_X >= VGA_WIDTH)
		{
			VGA_X = 0;
			VGA_Y ++;
		}
		
		if (VGA_Y >= VGA_HEIGHT)
		{
			vgaScroll(VGA_Y - VGA_HEIGHT + 1);
			VGA_Y = VGA_HEIGHT - 1;
		}
		
		vgaSetCursor(VGA_X, VGA_Y);
		vgaUpdate();	//This is probably inefficient here. Move it to the end of a print method later
	}
	
	void vgaPrintf(const char* string)
	{
		if (string == nullptr)
			return;
		
		uint32 i = 0;
		while (string[i] != '\0')
		{
			bool output = true;
			
			if (string[i] == '\\') //We've reached an escape code!
			{
				if (string[i + 1] == '%' && (string[i + 2] == 'B' || string[i + 2] == 'C') && getValueFromHexChar(string[i + 2]) != -1) //If the thing afterwards is a recognised escape code...
				{
					vgaPutChar(string[i + 1]);
					i += 1;
					output = false;
				}
			}
			else if (string[i] == '%') //We've come across a formatting code. This system is clever and interprets "%Bx" and "%Cx" as colour formatters.
			{
				bool cancel_escape = false;
				
				if (i > 0) //Make sure we can escape the formatter if we want to
				{
					if (string[i - 1] == '\\')
						cancel_escape = true;
				}
				
				if (string[i + 1] == 'C' && !cancel_escape)
				{
					VGAColor col = (VGAColor)getValueFromHexChar(string[i + 2]);
					
					if (col != -1)
					{
						VGA_FRONT_COL = col;
						i += 2;
						output = false;
					}
				}
				else if (string[i + 1] == 'B' && !cancel_escape)
				{
					VGAColor col = (VGAColor)getValueFromHexChar(string[i + 2]);
					
					if (col != -1)
					{
						VGA_BACK_COL = col;
						i += 2;
						output = false;
					}
				}
			}
			
			if (output)
				vgaPutChar(string[i]);
			
			i ++;
		}
	}
	
	void vgaPuts(const char* string)
	{
		if (string == nullptr)
			return;
		
		for (uint32 i = 0; string[i] != '\0'; i ++)
		{
			vgaPutChar(string[i]);
		}
	}
	
	void vgaDrawTextIcon(const char* icon, uint16 w, uint16 h)
	{
		for (uint16 i = 0; i < w * h; i ++)
		{
			vgaPutChar(icon[i]);
			
			if (i % w == w - 1)
				vgaPutChar('\n');
		}
	}
	
	// Utility functions
	int8 getValueFromHexChar(char character)
	{
		if ((character >= '0' && character <= '9') || (character >= 'A' && character <= 'F'))
			return ((character >= '0' && character <= '9') ? (character - '0') : (character - 'A' + 10));
		else
			return -1;
	}
}
