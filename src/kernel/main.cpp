#if defined(__linux__)
	#error "No cross-compiler in use. Cannot compile"
#endif

//Make sure it only compiles with 32-bit x86 targets
#if !defined(__i386__)
	#error "Must be compiled with an i686 elf cross-compiler"
#endif

#include "kernel.h"

extern "C" //Use C to link kernelStart
void kernelStart()
{
	Kernel kernel;
	kernel.init();
}
