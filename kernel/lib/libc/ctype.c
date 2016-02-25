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
* Name:         ctype.c
* 
* Description:  C standard library to classify & manipulate characters
* 
* Notes:        NONE
*/

// Character conversion functions
int toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return 'A' - 'a' + c;
	return c;
}

int tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return 'a' - 'A' + c;
	return c;
}
