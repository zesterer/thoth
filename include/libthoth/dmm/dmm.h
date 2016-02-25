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
* Name:         dmm.h
* 
* Description:  Dynamic Memory Manager
* 
* Notes:        NONE
*/

#ifndef LIBTHOTH_DMM_DMM_H
#define LIBTHOTH_DMM_DMM_H

#include "libthoth/type.h"

int dmm_set(addr base, sysint end);
addr dmm_allocate_block(sysint size);
int dmm_free_block(addr pointer);
void dmm_print_map(sysint start, sysint end);

#endif
