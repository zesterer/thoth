/*
* This file is part of Thoth.
* 
* Copyright (C) 2016  Joshua Barretto <joshua.s.barretto@gmail.com>
* 
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

/*
* Name:         stdlib.c
* 
* Description:  C standard library functions
* 
* Notes:        NONE
*/

// Local
#include "libc/stdlib.h"

// libthoth
#include "libthoth/dmm/dmm.h"

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

char* itoa(int value, char* str, int base)
{
	long v = 1;
	int i = 0;
	
	if (base < 2 || base > 32)
		return str;
	
	if (value < 0 && base == 10)
	{
		str[i] = '-';
		i ++;
	}
	
	value = abs(value);
	
	while (v < ((long)1 << (sizeof(int) * 8)))
		v *= base;
	
	while (v > 0)
	{
		if (value / v > 0)
		{
			if ((value / v) % base > 9)
				str[i] = 'A' + (value / v) % base - 10;
			else
				str[i] = '0' + (value / v) % base;
			
			i ++;
		}
		v /= base;
	}
	
	str[i] = '\0';
	return str;
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
	dmm_free_block(ptr);
}

void* malloc(size_t size)
{
	return dmm_allocate_block(size);
}

/* Integer arithmetics */

int abs(int n)
{
	return n < 0 ? -n : n;
}
