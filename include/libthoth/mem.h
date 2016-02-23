#ifndef LIBTHOTH_MEM_H
#define LIBTHOTH_MEM_H

#include "libthoth/types.h"

namespace thoth
{
	int memSetDMM(void* base, void* end);
	void* memAllocateBlock(size_t size);
	int memFreeBlock(void* pointer);
	void memPrintMap(size_t start, size_t end);
}

#endif
