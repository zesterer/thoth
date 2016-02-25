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
* Name:         dmm.c
* 
* Description:  Dynamic Memory Manager
* 
* Notes:        NONE
*/

#include "libthoth/dmm/dmm.h"

#include "libc/stdio.h"
#include "libc/string.h"

static int block_size = 1024; // The default size of memory blocks within the dmm
static bool dmm_is_valid = false; //Don't do stuff until we're sure we have a valid memory section for the dmm.

static addr dmm_base = NULL;
static addr dmm_start = NULL;
static sysint dmm_size = 00; //In blocks, not bytes

static byte* dmm_map = NULL;

static const sysint dmm_map_entry_size = 1;
static const byte MAP_EMPTY = 0x00;
static const byte MAP_FILLED = 0x01;
static const byte MAP_TAIL = 0x02;

sysint dmm_create_map();

int dmm_set(addr base, sysint size)
{
	if (((sysint)base + block_size + dmm_map_entry_size) < ((sysint)base + size)) //If we have enough memory space for at least one block
	{
		dmm_size = size / (1 + block_size);
		dmm_base = (addr)((sysint)base);
		dmm_start = (addr)((sysint)dmm_base + dmm_create_map());
		
		dmm_is_valid = true;
		
		//printf("Allocated DMM in memory\n");
		return 0;
	}
	else
	{
		//printf("%C4Error%CF: %C4Attempted to define space for a DMM, but there is not enough to contain a single block%CF");
		return 1;
	}
}

sysint dmm_create_map()
{
	//Clear the map. We really should do this since there could be call kinds of stuff already in the RAM
	for (sysint i = 0; i < dmm_size; i ++)
	{
		dmm_map[i] = MAP_EMPTY;
	}
	return dmm_size * dmm_map_entry_size;
}

addr dmm_allocate_block(sysint size)
{
	if (!dmm_is_valid)
		printf("%C4Error%CF: %C4Tried to allocate DMM memory block, but the dmm has not been created yet%CF");
	
	if (size <= 0)
		printf("%C4Error%CF: %C4Tried to allocate DMM memory block, but size was zero%CF");
	
	sysint blocks_needed = ((size - 1) / block_size) + 1;
	
	for (sysint i = 0; i < dmm_size; i ++)
	{
		if (dmm_map[i] == MAP_EMPTY) //Found an empty block, let's see if it's the right size
		{
			//printf("Found free block!\n");
			bool enough_space = true;
			
			//Loop through the map and check for space
			for (sysint j = i; j < dmm_size; j ++)
			{
				if (dmm_map[j] == MAP_EMPTY)
				{
					if ((j - i + 1) >= blocks_needed) // We've found enough space!
					{
						enough_space = true;
						break;
					}
				}
				else //It's not empty so we can't use this slot
				{
					enough_space = false;
					//printf("But it's not big enough!\n");
					break;
				}
			}
			
			if ((dmm_size - i) < blocks_needed) //Deal with the edge case when we're searching off the end of the dmm
				enough_space = false;
			
			if (enough_space)
			{
				//Make sure we fill in the blocks
				for (sysint j = i + 1; j < (i + blocks_needed); j ++)
					dmm_map[j] = MAP_TAIL;
				dmm_map[i] = MAP_FILLED;
				
				return &((byte*)dmm_start)[i * block_size];
			}
		}
	}
	
	//Couldn't find enough space
	printf("%C4Error%CF: %C4Attempted to allocate block on DMM, but there is not enough free space%CF");
	return NULL;
}

int dmm_free_block(addr pointer)
{
	if (!dmm_is_valid)
	{
		printf("%C4Error%CF: %C4Tried to free DMM memory block, but the dmm has not been created yet%CF");
		return 1;
	}
	
	if (pointer < dmm_start || (sysint)pointer > ((sysint)dmm_start + dmm_size * block_size))
	{
		printf("%C4Error%CF: %C4Pointer to free is not within DMM bounds%CF");
		return 2;
	}
	
	if (((sysint)pointer - (sysint)dmm_start) % block_size != 0)
	{
		printf("%C4Error%CF: %C4Pointer to free was not aligned to DMM blocks%CF");
		return 3;
	}
	
	sysint map_location = ((sysint)pointer - (sysint)dmm_start) / block_size;
	
	if (dmm_map[map_location] == MAP_FILLED)
	{
		//Free it
		dmm_map[map_location] = MAP_EMPTY;
		for (sysint i = map_location + 1; dmm_map[i] == MAP_TAIL && i < dmm_size; i ++)
			dmm_map[i] = MAP_EMPTY;
		//printf("Freed block from dmm\n");
		return 0;
	}
	else if (dmm_map[map_location] == MAP_TAIL)
	{
		printf("%C4Error%CF: %C4Pointer to free is not a heading block%CF");
		return 4;
	}
	else if (dmm_map[map_location] == MAP_EMPTY)
	{
		printf("%C4Error%CF: %C4Pointer to free is already free%CF");
		return 5;
	}
	else
	{
		printf("%C4Error%CF: %C4dmm corruption, invalid map entry detected in DMM%CF");
		dmm_is_valid = false; //Something went seriously wrong, so tell it to just stop
		return 4;
	}
	
	return 1;
}

void dmm_print_map(sysint start, sysint end)
{
	for (sysint i = start; i < end && i < dmm_size; i ++)
	{
		if (dmm_map[i] == MAP_FILLED)
			puts("H");
		else if (dmm_map[i] == MAP_TAIL)
			puts("T");
		else
			puts("-");
	}
	putchar('\n');
}
