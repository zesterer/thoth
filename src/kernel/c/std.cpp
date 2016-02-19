//----LOCAL----
#include "std.h"

namespace SquidOS
{
	namespace Kernel
	{
		namespace C
		{
			char int_to_char(uint8_t v)
			{
				return (char)(48 + v % 10);
			}

			size_t strlen(const char* str)
			{
				size_t ret = 0;
				while (str[ret] != 0)
					ret ++;
				return ret;
			}
			
			void wait(uint32_t time)
			{
				volatile uint32_t i = time;
				while (i != 0)
					i --;
			}
			
			uint8_t inb(uint16_t port)
			{
				uint8_t ret;
				asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
				return ret;
			}
			
			void outb(uint16_t port, uint8_t val)
			{
				asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
				/* TODO: Is it wrong to use 'N' for the port? It's not a 8-bit constant. */
				/* TODO: Should %1 be %w1? */
			}
			
			char getScancode()
			{
				char c = 0;
				
				while (true)
				{
					c = inb(0x60);
						
						return c;
					if (inb(0x60) != c)
					{
						c = inb(0x60);
						
						return c;
						
						if (c > 0)
						{
							lastCharacter = c;
							if (c == lastCharacter)
								C::wait(16000000);
							return c;
						}
					}
				}
			}
			
			char scancodeToCharacter(char c)
			{
				/*//Numbers
				if (c >= 0x02 && c < 0x0C)
					return 0x30 + (c - 1) % 10;
				
				//Top keyboard row
				if (c >= 0x10 && c < 0x1D)
					return "qwertyuiop[]\n"[c - 0x10];*/
				
				return "!!1234567890-=!!qwertyuiop[]!!asdfghjkl;'#!\\zxcvbnm,./!!! !FFFFFFFFFF!"[c];
				
				return c;
			}
			
			bool areInterruptsEnabled()
			{
				unsigned long flags;
				asm volatile ( "pushf\n\t"
						       "pop %0"
						       : "=g"(flags) );
				return flags & (1 << 9);
			}
			
			void cpuid(int code, uint32_t* a, uint32_t* d)
			{
				asm volatile ( "cpuid" : "=a"(*a), "=d"(*d) : "0"(code) : "ebx", "ecx" );
			}
			
			void lidt(void* base, uint16_t size)
			{
				struct
				{
					uint16_t length;
					uint32_t base;
				} __attribute__((packed)) IDTR;
			 
				IDTR.length = size;
				IDTR.base = (uint32_t) base;
				//asm ("lidt %0" : : "p" (&IDTR));
			}
		}
	}
}
