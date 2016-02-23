#include "libc/stdlib.h"

#include "libthoth/mem.h"

/* String conversion */

int atoi(const char* str)
{
	int sign = 1;
	int total = 0;
	
	for (size_t i = 0; str[i] != '\0'; i ++)
	{
		total *= 10;
		
		if (str[i] == '-')
			sign *= -1;
		else if (str[i] == '+')
			sign *= 1;
		else if (str[i] >= 48 && str[i] <= 58)
			total += str[i] - 48;
		else
			return 0;
	}
	
	return total * sign;
}

/* Pseudo-random sequence generation */

static unsigned long next_rand = 1;

int rand()
{
	next_rand = next_rand * 1103515245 + 12345;
	return (unsigned long)(next_rand / 65536) % 32768;
}

void srand(unsigned int seed)
{
	next_rand = seed;
}

/* Dynamic memory allocation */

void free(void* ptr)
{
	thoth::memFreeBlock(ptr);
}

void* malloc(size_t size)
{
	return thoth::memAllocateBlock(size);
}

void* operator new(size_t size)
{
	return malloc(size);
}
