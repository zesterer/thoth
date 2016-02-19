#if defined(__linux__)
	#error "No cross-compiler in use. Cannot compile"
#endif

//Make sure it only compiles with 32-bit x86 targets
#if !defined(__i386__)
	#error "Must be compiled with an i686 elf cross-compiler"
#endif

//----LOCAL----
//#include "kernel.h"

#include "thoth/vga.h"
#include "thoth/assert.h"

extern "C" //Use C to link kernel_main
void kernelStart()
{
	//SquidOS::Kernel::Kernel kernel;
	//kernel.initialize();
	
	thoth::vgaInit();
	
	thoth::assert(true, "Initialised C++ environment");
	thoth::assert(true, "Initialised text-mode VGA buffer");
	thoth::puts("\n");
	
	thoth::puts("Welcome to the Thoth operating system");
}
