#ifndef KERNEL_GDT_H
#define KERNEL_GDT_H

#include "thoth/types.h"

struct GDT
{
	uint16 limit;
	uint32 base;
} __attribute__((packed));

#endif
