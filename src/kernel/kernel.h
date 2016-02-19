#ifndef KERNEL_KERNEL_H
#define KERNEL_KERNEL_H

//----LOCAL----
#include "terminal/terminal.h"

namespace SquidOS
{
	namespace Kernel
	{
		struct Kernel
		{
			Terminal::Terminal terminal;
			
			uint64_t IDT;
		
			void initialize();
		};
	}
}

#endif
