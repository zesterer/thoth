#ifndef LIBTHOTH_DMM_DMM_H
#define LIBTHOTH_DMM_DMM_H

#include "libthoth/type.h"

int dmm_set(addr base, sysint end);
addr dmm_allocate_block(sysint size);
int dmm_free_block(addr pointer);
void dmm_print_map(sysint start, sysint end);

#endif
