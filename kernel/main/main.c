#ifdef __linux__
	#error "No cross-compiler in use. Cannot compile"
#endif

#ifndef __ELF__
	#error "Must be compiled with an elf cross-compiler"
#endif

#include "kernel.h"

extern "C"
void kernel_start()
{
	kernel_init();
}
