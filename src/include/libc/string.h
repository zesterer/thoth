#ifndef LIBC_STRING_H
#define LIBC_STRING_H

#include "stddef.h"

//Copying
void* memcpy(void* destination, const void* source, size_t num);
void* memmove(void* destination, const void* source, size_t num);
char* strcpy(char* destination, const char* source);
char* strncpy(char* destination, const char* source, size_t num);

//Concatenation
char* strcat(char* destination, const char* source);
char* strncat(char* destination, const char* source, size_t num);

//TODO - The rest

#endif
