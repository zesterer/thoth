#ifndef LIBC_STDIO_H
#define LIBC_STDIO_H

#ifdef _cplusplus
extern "C"
{
#endif

#include "stddef.h"

//Macros
#define EOF -1

//Operations on files
//TODO

//File access
//TODO

//Formatted input/output
int printf(const char* format, ...);
//TODO - complete this

//Character input/output
int putchar(int character);
int puts(const char* str);
//TODO - complete this

//Direct input/output
//TODO

//File positioning
//TODO

//Error-handling
//TODO

#ifdef _cplusplus
}
#endif

#endif
