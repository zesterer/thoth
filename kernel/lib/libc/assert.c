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
* Name:         assert.c
* 
* Description:  Function to assert values during execution
* 
* Notes:        NONE
*/

// Local
#include "libc/assert.h"
#include "libc/stdio.h"

bool _assert(const char* assert_str, bool assert_val)
{
	if (!assert_val)
	{
		printf("Assertion '");
		printf(assert_str);
		printf("' failed.\n");
	}
	
	return assert_val;
}

bool _assert_test(const char* assert_str, bool assert_val, const char* message)
{
	if (assert_val)
		printf("%C2SUCCESS%CF: ");
	else
		printf("%C4FAILURE%CF: ");
	
	printf(message);
	putchar('\n');
	
	return assert_val;
}
