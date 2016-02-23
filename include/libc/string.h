#ifndef LIBC_STRING_H
#define LIBC_STRING_H

#ifdef _cplusplus
extern "C"
{
#endif


#include "stddef.h"

//Copying
void* memcpy(void* destination, const void* source, size_t num);
void* memmove(void* destination, const void* source, size_t num);
char* strcpy(char* destination, const char* source);
char* strncpy(char* destination, const char* source, size_t num);

//Concatenation
char* strcat(char* destination, const char* source);
char* strncat(char* destination, const char* source, size_t num);

//Comparasion
int memcmp(const void* ptr1, const void* ptr2, size_t num);
int strcmp(const char* str1, const char* str2);
int strcoll(const char* str1, const char* str2);
int strncmp(const char* str1, const char* str2, size_t num);
size_t strxfrm(char* destination, const char* source, size_t num);

//Searching
void* memchr(void* ptr, int value, size_t num);

//Other
void* memset(void* ptr, int value, size_t num);
size_t strlen(const char* str);

#ifdef _cplusplus
}
#endif

#endif
