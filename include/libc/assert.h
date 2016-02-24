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
* Name:         assert.h
* 
* Description:  Function to assert values during execution
* 
* Notes:        NONE
*/

#ifndef LIBC_ASSERT_H
#define LIBC_ASSERT_H

// Local
#include "libc/stdio.h"

// libthoth
#include "libthoth/type.h"

#define assert(ASSERTION) _assert(#ASSERTION, ASSERTION)
#define assert_test(ASSERTION, MESSAGE) _assert_test(#ASSERTION, ASSERTION, MESSAGE)

bool _assert(const char* assert_str, bool assert_val);
bool _assert_test(const char* assert_str, bool assert_val, const char* message);

#endif
