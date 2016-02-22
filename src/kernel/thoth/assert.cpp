#include "assert.h"

#include "vga.h"

#include "stdio.h"

namespace thoth
{
	bool assert(bool test, const char* message)
	{
		if (test)
			printf("%C2SUCCESS%CF  ");
		else
			printf("%C4FAILURE%CF  ");
		
		puts(message);
		puts("\n");
		
		return test;
	}
}
