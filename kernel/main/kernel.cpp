#include "kernel.h"

#include "libthoth/vga.h"
#include "libthoth/assert.h"
#include "libthoth/sys.h"
#include "libthoth/mem.h"

#include "libc/stdlib.h"
#include "libc/stdio.h"
#include "libc/string.h"

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
	//asm volatile("mov $(0xB8000 + 0x0), %rax\n"
	//"movb $33, (%rax)\n"
	//"jmp _hang_cpu");
	thoth::vgaInit();
	
	thoth::assert(true, "Set up temporary stack");
	thoth::assert(true, "Initialised GDT and paging tables");
	thoth::assert(true, "Switched to 64-bit long mode");
	thoth::assert(true, "Initialised stable environment");
	thoth::assert(true, "Jumped to kernel entry location");
	thoth::assert(true, "Initialised text-mode VGA buffer");
	
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
	
	puts("\nBegin testing C standard library...\n\n");
	
	//Allocate a dynamic memory manager 1MB after the end of the kernel of size 16MB
	thoth::memSetDMM((void*)((size_t)(&_end_of_kernel) + 0x100000), (void*)((size_t)(&_end_of_kernel) + 0x1000000 - 1));
	
	thoth::memPrintMap(0, 40);
	void* a = malloc(4096); printf("\tAllocated a chunk of data 'a' of size 4096 bytes\n");
	thoth::memPrintMap(0, 40);
	void* b = malloc(4096); printf("\tAllocated a chunk of data 'b' of size 4096 bytes\n");
	thoth::memPrintMap(0, 40);
	free(a); printf("\tFreed chunk of data 'a' of size 4096 bytes\n");
	thoth::memPrintMap(0, 40);
	void* c = malloc(1024); printf("\tAllocated a chunk of data 'c' of size 1024 bytes\n");
	thoth::memPrintMap(0, 40);
	void* d = malloc(2048); printf("\tAllocated a chunk of data 'd' of size 2048 bytes\n");
	thoth::memPrintMap(0, 40);
	void* e = malloc(2048); printf("\tAllocated a chunk of data of size 2048 bytes\n");
	thoth::memPrintMap(0, 40);
	free(c); printf("\tFreed chunk of data 'c' of size 1024 bytes\n");
	thoth::memPrintMap(0, 40);
}
