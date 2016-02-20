#include "kernel.h"

#include "thoth/vga.h"
#include "thoth/assert.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

void Kernel::init()
{
	thoth::vgaInit();
	
	thoth::assert(true, "Initialised C++ environment");
	thoth::assert(true, "Jumped to kernel entry location");
	thoth::assert(true, "Initialised text-mode VGA buffer");
	
	this->run();
}

void Kernel::run()
{
	thoth::puts("\n");
	
	thoth::puts("~ Welcome to the Thoth operating system ~\n");
	
	thoth::puts("\nBegin testing C standard library...\n\n");
	
	//Pseudo-random sequence generation
	
	thoth::puts("Pseudo-random sequence generation...");
	srand(1337);
	char l[2] = "A";
	for (int i = 0; i < 10; i ++)
	{
		l[0] = 'A' + rand() % 26;
		thoth::puts(l);
	}
	thoth::puts("\n\n");
	
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
}
