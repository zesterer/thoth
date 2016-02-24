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
* Name:         stream.h
* 
* Description:  A generic interface to stream objects
* 
* Notes:        NONE
*/

#ifndef LIBTHOTH_STREAM_STREAM_H
#define LIBTHOTH_STREAM_STREAM_H

// Local
#include "libthoth/type.h"

// Stream definition
struct stream;

// Stream utility functions
typedef void (*fptr_stream_init)(stream* strm);
typedef void (*fptr_stream_write_byte)(stream* strm, byte value);
typedef void (*fptr_stream_write)(stream* strm, const byte* data, sysint size);

// Stream implementation
struct stream
{
	fptr_stream_init init;
	fptr_stream_write_byte write_byte;
	fptr_stream_write write;
};

#endif
