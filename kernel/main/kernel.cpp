#include "kernel.h"

#include "libthoth/vga.h"
#include "libthoth/assert.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

//static char* thoth_logo = (char*)"          ________         _____ _           _   _         _____/ o  \\   \\_      |_   _| |__   ___ | |_| |__     / ____     |     \\       | | | '_ \\ / _ \\| __| '_ \\   //     \\    /      |      | | | | | | (_) | |_| | | |  '       )__(______/       |_| |_| |_|\\___/ \\__|_| |_|";

static char* thoth_logo = (char*)"##################...######...#...####........###..##.....###.####...####.###....#######....########.....######.........###.........####........";

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
	
	//Pseudo-random sequence generation
	
	puts("Pseudo-random sequence generation...");
	srand(1337);
	char l[2] = "A";
	for (int i = 0; i < 10; i ++)
	{
		l[0] = 'A' + rand() % 26;
		puts(l);
	}
	puts("\n\n");
	
	// String conversion
	
	thoth::assert(atoi("5") == 5, "Numerical conversion: atoi(\"5\") == 5");
	thoth::assert(atoi("12704") == 12704, "Numerical conversion: atoi(\"12704\") == 12704");
	thoth::assert(atoi("-14") == -14, "Numerical conversion: atoi(\"-14\") == -14");
	thoth::assert(atoi("--875") == 875, "Numerical conversion: atoi(\"--875\") == 875");
	
	//stdio.h
	
	puts("\nThis message is a test of puts() in stdio.h, and the following '!' is a test of putchar(): ");
	putchar('!');
	puts("\n\n");
	
	thoth::assert(strlen("Test") == 4, "Value of strlen(\"Test\") == 4");
	thoth::assert(strlen("") == 0, "Value of strlen(\"\") == 0");
	thoth::assert(strlen("Test\0Message") == 4, "Value of strlen(\"Test\\0Message\") == 4\n");
	
	puts("\n\n\n");
}
