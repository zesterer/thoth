#include "libthoth/mem.h"

#include "libc/stdio.h"
#include "libc/string.h"

namespace thoth
{
	static int block_size = 1024; // The default size of memory blocks within the dmm
	static bool dmm_is_valid = false; //Don't do stuff until we're sure we have a valid memory section for the dmm.
	
	static void* dmm_base = nullptr;
	static void* dmm_start = nullptr;
	static size_t dmm_size = 00; //In blocks, not bytes
	
	static byte* dmm_map = nullptr;
	
	static const size_t dmm_map_entry_size = 1;
	static const byte MAP_EMPTY = 0x00;
	static const byte MAP_FILLED = 0x01;
	static const byte MAP_TAIL = 0x02;
	
	size_t createdmmMap();
	
	int memSetDMM(void* base, size_t size)
	{
		if (((size_t)base + block_size + dmm_map_entry_size) < ((size_t)base + size)) //If we have enough memory space for at least one block
		{
			dmm_size = size / (1 + block_size);
			dmm_base = (void*)((size_t)base);
			dmm_start = (void*)((size_t)dmm_base + createdmmMap());
			
			dmm_is_valid = true;
			
			printf("Allocated DMM in memory\n");
			return 0;
		}
		else
		{
			printf("%C4Error%CF: %C4Attempted to define space for a dmm, but there is not enough to contain a single block%CF");
			return 1;
		}
	}
	
	size_t createdmmMap()
	{
		//Clear the map. We really should do this since there could be call kinds of stuff already in the RAM
		for (size_t i = 0; i < dmm_size; i ++)
		{
			dmm_map[i] = MAP_EMPTY;
		}
		return dmm_size * dmm_map_entry_size;
	}
	
	void* memAllocateBlock(size_t size)
	{
		if (!dmm_is_valid)
			printf("%C4Error%CF: %C4Tried to allocate dmm memory block, but the dmm has not been created yet%CF");
		
		if (size <= 0)
			printf("%C4Error%CF: %C4Tried to allocate dmm memory block, but size was zero%CF");
		
		size_t blocks_needed = ((size - 1) / block_size) + 1;
		
		for (size_t i = 0; i < dmm_size; i ++)
		{
			if (dmm_map[i] == MAP_EMPTY) //Found an empty block, let's see if it's the right size
			{
				//printf("Found free block!\n");
				bool enough_space = true;
				
				//Loop through the map and check for space
				for (size_t j = i; j < dmm_size; j ++)
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
					for (size_t j = i + 1; j < (i + blocks_needed); j ++)
						dmm_map[j] = MAP_TAIL;
					dmm_map[i] = MAP_FILLED;
					
					return &((byte*)dmm_start)[i * block_size];
				}
			}
		}
		
		//Couldn't find enough space
		printf("%C4Error%CF: %C4Attempted to allocate block on dmm, but there is not enough free space%CF");
		return nullptr;
	}
	
	int memFreeBlock(void* pointer)
	{
		if (!dmm_is_valid)
		{
			printf("%C4Error%CF: %C4Tried to free dmm memory block, but the dmm has not been created yet%CF");
			return 1;
		}
		
		if (pointer < dmm_start || (size_t)pointer > ((size_t)dmm_start + dmm_size * block_size))
		{
			printf("%C4Error%CF: %C4Pointer to free is not within dmm bounds%CF");
			return 2;
		}
		
		if (((size_t)pointer - (size_t)dmm_start) % block_size != 0)
		{
			printf("%C4Error%CF: %C4Pointer to free was not aligned to dmm blocks%CF");
			return 3;
		}
		
		size_t map_location = ((size_t)pointer - (size_t)dmm_start) / block_size;
		
		if (dmm_map[map_location] == MAP_FILLED)
		{
			//Free it
			dmm_map[map_location] = MAP_EMPTY;
			for (size_t i = map_location + 1; dmm_map[i] == MAP_TAIL && i < dmm_size; i ++)
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
			printf("%C4Error%CF: %C4dmm corruption, invalid map entry detected%CF");
			dmm_is_valid = false; //Something went seriously wrong, so tell it to just stop
			return 4;
		}
		
		return 1;
	}
	
	void memPrintMap(size_t start, size_t end)
	{
		for (size_t i = start; i < end; i ++)
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
}
