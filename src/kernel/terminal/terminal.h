#ifndef KERNEL_TERMINAL_TERMINAL_H
#define KERNEL_TERMINAL_TERMINAL_H

//----LOCAL----
#include "../c/std.h"

namespace SquidOS
{
	namespace Kernel
	{
		namespace Terminal
		{
			enum VGAColor
			{
				BLACK = 0,
				BLUE = 1,
				GREEN = 2,
				CYAN = 3,
				RED = 4,
				MAGENTA = 5,
				BROWN = 6,
				LIGHT_GREY = 7,
				DARK_GREY = 8,
				LIGHT_BLUE = 9,
				LIGHT_GREEN = 10,
				LIGHT_CYAN = 11,
				LIGHT_RED = 12,
				LIGHT_MAGENTA = 13,
				LIGHT_BROWN = 14,
				WHITE = 15,
				
				TRANSPARENT = 1337,
			};
	
			static const size_t VGA_WIDTH = 80;
			static const size_t VGA_HEIGHT = 25;
			static const uint16_t* VGA_MEMORY = (uint16_t*)0xB8000;
	
			struct Terminal
			{
				size_t terminal_x;
				size_t terminal_y;
				uint16_t* terminal_buffer;
		
				void initialize();
				void writeChar(char c, VGAColor fore = VGAColor::TRANSPARENT, VGAColor back = VGAColor::TRANSPARENT);
				void writeString(const char* str, VGAColor fore = VGAColor::TRANSPARENT, VGAColor back = VGAColor::TRANSPARENT);
				void printTest(const char* str, bool success = true);
				
				void setForeColor(size_t x, size_t y, VGAColor color);
				void setBackColor(size_t x, size_t y, VGAColor color);
				void setCharacter(size_t x, size_t y, char character);
				void setText(size_t x, size_t y, char character, VGAColor fore = VGAColor::TRANSPARENT, VGAColor back = VGAColor::TRANSPARENT);
			};
		}
	}
}

#endif
