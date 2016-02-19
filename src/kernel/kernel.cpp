//----LOCAL----
#include "kernel.h"

#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define VERSION_RELEASE 1

#define BAT_SIZE 6

namespace SquidOS
{
	namespace Kernel
	{
		int sign(int x)
		{
			if (x > 0)
				return 1;
			if (x < 0)
				return -1;
			return 0;
		}
		
		void Kernel::initialize()
		{
			//Initialize terminal
			this->terminal.initialize();
			
			terminal.printTest("Bootstrap initialization", true);
			terminal.printTest("Kernel instancing", true);
			terminal.printTest("Terminal initialization", true);
			terminal.printTest("Interrupt request enabling", C::areInterruptsEnabled());
			
			terminal.writeString("\n", Terminal::VGAColor::WHITE, Terminal::VGAColor::BLACK);
			for (int i = Terminal::VGA_WIDTH; i > 0; i --)
				terminal.writeChar('-', Terminal::VGAColor::WHITE, Terminal::VGAColor::BLACK);
			terminal.writeString("\n", Terminal::VGAColor::WHITE, Terminal::VGAColor::BLACK);
	
			terminal.writeString("SquidOS v", Terminal::VGAColor::WHITE, Terminal::VGAColor::BLACK);
			terminal.writeChar(C::int_to_char(VERSION_MAJOR), Terminal::VGAColor::WHITE, Terminal::VGAColor::BLACK);
			terminal.writeChar('.', Terminal::VGAColor::WHITE, Terminal::VGAColor::BLACK);
			terminal.writeChar(C::int_to_char(VERSION_MINOR), Terminal::VGAColor::WHITE);
			terminal.writeChar('.', Terminal::VGAColor::WHITE, Terminal::VGAColor::BLACK);
			terminal.writeChar(C::int_to_char(VERSION_RELEASE), Terminal::VGAColor::WHITE, Terminal::VGAColor::BLACK);
			terminal.writeString("\n", Terminal::VGAColor::WHITE, Terminal::VGAColor::BLACK);
	
			terminal.writeString("\n> Welcome to SquidOS\n", Terminal::VGAColor::RED);
			terminal.writeString("> If you see this text, then congratulations. The kernel booted correctly.\n", Terminal::VGAColor::GREEN);
			terminal.writeString("> If you don't see this text, something went horribly wrong.\n", Terminal::VGAColor::GREEN);
			
			terminal.writeString("$> ", Terminal::VGAColor::LIGHT_RED);
			
			//C::lidt((void*)this->IDT, 256);
			
			C::wait(256000000);
			
			int bat0 = 10;
			int bat1 = 10;
			
			float ballx = 0.0f;
			float bally = 0.0f;
			float ballh = 1.0f;
			float ballv = 0.5f;
			
			bool keys[4];
			
			bool conbuff[2][Terminal::VGA_WIDTH][Terminal::VGA_HEIGHT];
			
			conbuff[0][4][4] = true;
			conbuff[0][5][5] = true;
			conbuff[0][5][6] = true;
			conbuff[0][4][6] = true;
			conbuff[0][3][6] = true;
			
			conbuff[0][14][24] = true;
			conbuff[0][13][25] = true;
			conbuff[0][13][26] = true;
			conbuff[0][14][26] = true;
			conbuff[0][15][26] = true;
			
			int tick = 0;
			
			while (true)
			{
				C::wait(6400000);
				//terminal.writeChar('.', Terminal::VGAColor::LIGHT_BLUE);
				
				if (true)
				{
					char code = C::getScancode();
				
					switch (code)
					{
						case 0x91:
							keys[0] = false;
							break;
						case 0x11:
							keys[0] = true;
							break;
						case 0x9F:
							keys[1] = false;
							break;
						case 0x1F:
							keys[1] = true;
							break;
					
						case 0x97:
							keys[2] = false;
							break;
						case 0x17:
							keys[2] = true;
							break;
						case 0xA5:
							keys[3] = false;
							break;
						case 0x25:
							keys[3] = true;
							break;
					
						default:
							break;
					}
				
					if (code == 0x91)
						ballh *= 5.0f;
				
					bally += ballv;
					ballx += ballh;
				
					if (ballx <= 0 || ballx >= Terminal::VGA_WIDTH - 1)
						ballh *= -1.0f;
					if (bally <= 0 || bally >= Terminal::VGA_HEIGHT - 1)
						ballv *= -1.0f;
					
					if (keys[0])
						bat0 --;
					if (keys[1])
						bat0 ++;
				
					if (ballh < 0)
						bat0 += sign((int)(bally - BAT_SIZE / 2) - bat0);
				
					if (ballh > 0)
						bat1 += sign((int)(bally - BAT_SIZE / 2) - bat1);
				
					terminal.initialize();
				
					for (int i = 0; i < BAT_SIZE; i ++)
					{
						terminal.setText(0, bat0 + i, ' ', Terminal::VGAColor::WHITE, Terminal::VGAColor::RED);
						terminal.setText(Terminal::VGA_WIDTH - 1, bat1 + i, ' ', Terminal::VGAColor::WHITE, Terminal::VGAColor::BLUE);
					}
				
					terminal.setText(ballx, bally, ' ', Terminal::VGAColor::GREEN, Terminal::VGAColor::WHITE);
				}
				else
				{
					terminal.initialize();
					
					for (int x = 0; x < Terminal::VGA_WIDTH; x ++)
					{
						for (int y = 0; y < Terminal::VGA_HEIGHT; y ++)
						{
							conbuff[(tick + 1) % 2][x][y] = conbuff[tick % 2][x][y];
						}
					}
					
					//Conway
					for (int x = 0; x < Terminal::VGA_WIDTH; x ++)
					{
						for (int y = 0; y < Terminal::VGA_HEIGHT; y ++)
						{
							int a = Terminal::VGA_WIDTH;
							int b = Terminal::VGA_HEIGHT;
							int neighbours = 0;
							if (conbuff[tick % 2][(x - 1 + a) % Terminal::VGA_WIDTH][(y - 1 + b) % Terminal::VGA_HEIGHT]) neighbours ++;
							if (conbuff[tick % 2][(x + 0 + a) % Terminal::VGA_WIDTH][(y - 1 + b) % Terminal::VGA_HEIGHT]) neighbours ++;
							if (conbuff[tick % 2][(x + 1 + a) % Terminal::VGA_WIDTH][(y - 1 + b) % Terminal::VGA_HEIGHT]) neighbours ++;
							if (conbuff[tick % 2][(x - 1 + a) % Terminal::VGA_WIDTH][(y + 0 + b) % Terminal::VGA_HEIGHT]) neighbours ++;
							if (conbuff[tick % 2][(x + 1 + a) % Terminal::VGA_WIDTH][(y + 0 + b) % Terminal::VGA_HEIGHT]) neighbours ++;
							if (conbuff[tick % 2][(x - 1 + a) % Terminal::VGA_WIDTH][(y + 1 + b) % Terminal::VGA_HEIGHT]) neighbours ++;
							if (conbuff[tick % 2][(x + 0 + a) % Terminal::VGA_WIDTH][(y + 1 + b) % Terminal::VGA_HEIGHT]) neighbours ++;
							if (conbuff[tick % 2][(x + 1 + a) % Terminal::VGA_WIDTH][(y + 1 + b) % Terminal::VGA_HEIGHT]) neighbours ++;
							
							if (conbuff[tick % 2][x][y])
							{
								if (neighbours < 2)
									conbuff[(tick + 1) % 2][x][y] = false;
								if (neighbours > 3)
									conbuff[(tick + 1) % 2][x][y] = false;
							}
							else if (neighbours == 3)
								conbuff[(tick + 1) % 2][x][y] = true;
							
							if (conbuff[(tick + 1) % 2][x][y])
								terminal.setText(x, y, ' ', Terminal::VGAColor::BLACK, Terminal::VGAColor::GREEN);
						}
					}
				}
				
				tick ++;
			}
		}
	}
}
