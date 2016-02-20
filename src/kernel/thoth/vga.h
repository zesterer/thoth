#ifndef THOTH_VGA_H
#define THOTH_VGA_H

#include "types.h"

namespace thoth
{
	enum VGAColor
	{
		VGA_BLACK = 0,
		VGA_BLUE = 1,
		VGA_GREEN = 2,
		VGA_CYAN = 3,
		VGA_RED = 4,
		VGA_MAGENTA = 5,
		VGA_BROWN = 6,
		VGA_LIGHT_GREY = 7,
		VGA_DARK_GREY = 8,
		VGA_LIGHT_BLUE = 9,
		VGA_LIGHT_GREEN = 10,
		VGA_LIGHT_CYAN = 11,
		VGA_LIGHT_RED = 12,
		VGA_LIGHT_MAGENTA = 13,
		VGA_LIGHT_BROWN = 14,
		VGA_WHITE = 15,
	};
	
	void vgaInit();
	
	void vgaSetCharacter(uint16 x, uint16 y, char character);
	void vgaSetBackColor(uint16 x, uint16 y, VGAColor color);
	void vgaSetFrontColor(uint16 x, uint16 y, VGAColor color);
	
	void vgaSetCursor(uint16 x, uint16 y);
	
	void puts(const char* string, uint16 border = 0);
	void message(const char* string);
}

#endif
