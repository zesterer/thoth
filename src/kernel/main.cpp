#ifdef __linux__
	#error "No cross-compiler in use. Cannot compile"
#endif

#ifndef __i386__
	#error "Must be compiled with an i686 elf cross-compiler"
#endif

#include "kernel.h"

extern "C" //Use C to link kernelStart
void kernelStart()
{
	Kernel kernel;
	kernel.init();
}
