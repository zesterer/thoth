#include "assert.h"

#include "vga.h"

namespace thoth
{
	bool assert(bool test, const char* message)
	{
		if (test)
			puts("SUCCESS  ");
		else
			puts("FAILURE  ");
		
		puts(message);
		puts("\n");
		
		return test;
	}
}
