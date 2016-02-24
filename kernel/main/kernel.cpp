#include "kernel.h"

#include "libthoth/vga.h"
#include "libthoth/assert.h"
#include "libthoth/sys.h"
#include "libthoth/mem.h"

#include "libkernel/vga/vga.h"
#include "libkernel/vga/vgastream.h"

#include "libc/stdlib.h"
#include "libc/stdio.h"
#include "libc/string.h"

#include "libcpp/new"

//static char* thoth_logo = (char*)"          ________         _____ _           _   _         _____/ o  \\   \\_      |_   _| |__   ___ | |_| |__     / ____     |     \\       | | | '_ \\ / _ \\| __| '_ \\   //     \\    /      |      | | | | | | (_) | |_| | | |  '       )__(______/       |_| |_| |_|\\___/ \\__|_| |_|";

//static char* thoth_logo = (char*)"##################...######...#...####........###..##.....###.####...####.###....#######....########.....######.........###.........####........";

//A pointer to the end of the kernel
extern void* _end_of_kernel asm("_end_of_kernel");

struct Test
{
	int a;
	int b;
};

void Kernel::init()
{
	// Must come BEFORE any printing functions!
	vga_default_stream_init();
	
	thoth::assert(true, "Set up temporary stack");
	thoth::assert(true, "Initialised GDT and paging tables");
	thoth::assert(true, "Switched to 64-bit long mode");
	thoth::assert(true, "Initialised stable environment");
	thoth::assert(true, "Jumped to kernel entry location");
	thoth::assert(true, "Initialised text-mode VGA buffer");
	thoth::assert(thoth::getInterruptsEnabled(), "Testing for interrupts enabled");
	
	bool enabled_dmm = thoth::memSetDMM(&_end_of_kernel, 0x4000000) == 0;
	thoth::assert(enabled_dmm, "Setting up DMM");
	
	Kernel::run();
}

void Kernel::run()
{
	//thoth::vgaDrawTextIcon(thoth_logo, 12, 12);
	puts("\n");
	printf("%BF%C0Welcome to the %C6Thoth%C0 operating system%B0%CF\n");
	char version[6] = "X.Y.Z";
	version[0] = '0' + VERSION_MAJOR;
	version[2] = '0' + VERSION_MINOR;
	version[4] = '0' + VERSION_RELEASE;
	printf("Version %C4");
	printf(version);
	printf("%CF\n");
	
	/*puts("\nBegin testing C standard library...\n\n");
	
	//Allocate a dynamic memory manager after the end of the kernel of size 0x4000000 (64MB)
	thoth::memSetDMM(&_end_of_kernel, 0x2400);
	
	thoth::memPrintMap(0, 40);
	void* a = malloc(4096); printf("\tAllocated a chunk of data 'a' of size 4096 bytes\n");
	thoth::memPrintMap(0, 40);
	void* b = malloc(4096); printf("\tAllocated a chunk of data 'b' of size 4096 bytes\n");
	thoth::memPrintMap(0, 40);
	free(a); printf("\tFreed chunk of data 'a' of size 4096 bytes\n");
	thoth::memPrintMap(0, 40);
	void* c = malloc(3); printf("\tAllocated a chunk of data 'c' of size 3 bytes\n");
	thoth::memPrintMap(0, 40);
	void* d = malloc(2048); printf("\tAllocated a chunk of data 'd' of size 2048 bytes\n");
	thoth::memPrintMap(0, 40);
	void* e = malloc(2048); printf("\tAllocated a chunk of data of size 2048 bytes\n");
	thoth::memPrintMap(0, 40);
	free(c); printf("\tFreed chunk of data 'c' of size 1024 bytes\n");
	thoth::memPrintMap(0, 40);
	Test* atest = new Test();
	thoth::memPrintMap(0, 40);
	delete atest;
	thoth::memPrintMap(0, 40);*/
}
