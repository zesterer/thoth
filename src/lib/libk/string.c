#include "string.h"

/* Copying */

void* memcpy(void* destination, const void* source, size_t num)
{
	for (size_t i = 0; i < num; i ++)
		((unsigned char*)destination)[i] = ((unsigned char*)source)[i];
	
	return destination;
}

char* strcpy(char* destination, const char* source)
{
	for (size_t i = 0; source[i] != '\0'; i ++)
		destination[i] = source[i];
	
	return destination;
}

char* strncpy(char* destination, const char* source, size_t num)
{
	for (size_t i = 0; i < num && source[i] != '\0'; i ++)
		destination[i] = source[i];
	
	return destination;
}

//Concatenation
char* strcat(char* destination, const char* source)
{
	size_t len = strlen(destination);
	
	for (size_t i = 0; source[i] != '\0'; i ++)
		destination[i + len] = source[i];
	
	return destination;
}

/* Comparasion */

int strcmp(const char* str1, const char* str2)
{
	int i = 0;
	
	while (str1[i] == str2[i])
	{
		if (str2[i++] == 0)
			return 0;
	}
	
	return 1;
}

int strncmp(const char* str1, const char* str2, size_t num)
{
	int result = 0;
	
	while (num)
	{
		result = *str1 - *str2++;
		
		if (result != 0 || *str1++ == 0)
			break;
		
		num--;
	}
	
	return result;
}

/* Other */
void* memset(void* ptr, int value, size_t num)
{
	for (size_t i = 0; i < num; i ++)
		((unsigned char*)ptr)[i] = (unsigned char)value;
	
	return ptr;
}

size_t strlen(const char* str)
{
	size_t i;
	for (i = 0; str[i] != '\0'; i ++) {}
	return i;
}
