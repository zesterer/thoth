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
* Name:         term.h
* 
* Description:  Utilities to interface with services
* 
* Notes:        NONE
*/

#ifndef LIBTHOTH_TERM_TERM_H
#define LIBTHOTH_TERM_TERM_H

// Local
#include "libthoth/term/term.h"

// Terminal definition

// Service identifier
typedef uint64 service_id;

// Service utility functions
void service_communicate(service_id id, addr* response_message, sysint* response_size, addr, addr send_message, sysint send_size);

#endif
