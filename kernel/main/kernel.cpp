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
#include "libc/assert.h"

#include "libcpp/new"

//static char* thoth_logo = (char*)"          ________         _____ _           _   _         _____/ o  \\   \\_      |_   _| |__   ___ | |_| |__     / ____     |     \\       | | | '_ \\ / _ \\| __| '_ \\   //     \\    /      |      | | | | | | (_) | |_| | | |  '       )__(______/       |_| |_| |_|\\___/ \\__|_| |_|";

//static char* thoth_logo = (char*)"##################...######...#...####........###..##.....###.####...####.###....#######....########.....######.........###.........####........";

//A pointer to the end of the kernel
extern void* _end_of_kernel asm("_end_of_kernel");

void Kernel::init()
{
	// Must come BEFORE any printing functions!
	vga_default_stream_init();
	
	assert_test(true, "Set up temporary stack");
	assert_test(true, "Initialised GDT and paging tables");
	assert_test(true, "Switched to 64-bit long mode");
	assert_test(true, "Initialised stable environment");
	assert_test(true, "Jumped to kernel entry location");
	assert_test(true, "Initialised text-mode VGA buffer");
	assert_test(thoth::getInterruptsEnabled(), "Testing for interrupts enabled");
	
	char a[sizeof(int) * 8 + 1];
	for (int i = 2; i <= 16; i ++)
	{
		itoa(-137, a, i);
		printf(a);
		putchar('\n');
	}
	
	bool enabled_dmm = thoth::memSetDMM(&_end_of_kernel, 0x4000000) == 0;
	assert_test(enabled_dmm, "Setting up DMM");
	
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
}
