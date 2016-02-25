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
* Name:         stdlib.h
* 
* Description:  C standard library functions
* 
* Notes:        NONE
*/

#ifndef LIBC_STDLIB_H
#define LIBC_STDLIB_H

#ifdef _cplusplus
extern "C"
{
#endif

#include "stddef.h"

//Types
typedef struct {
  int quot;
  int rem;
} div_t;

typedef struct {
  long quot;
  long rem;
} ldiv_t;

typedef struct {
  long long quot;
  long long rem;
} lldiv_t;

//String conversion
int atoi(const char* str);
char* itoa(int value, char* str, int base);
//TODO

//Pseudo-random sequence generation
int rand();
void srand(unsigned int seed);

//Dynamic memory allocation
//TODO
//calloc
void free(void* ptr);
void* malloc(size_t size);
//realloc

//Environment
void abort();
void exit(int status);
char* getenv(const char* name);
int system(const char* command);

//Searching and sorting
//TODO

//Integer arithmetics
int abs(int n);
div_t div(int numer, int denom);
long labs(long n);
ldiv_t ldiv(long numer, long denom);
long long llabs(long long n);
lldiv_t lldiv(long long numer, long long denom);

//Multibyte characters
int mblen(const char* pmb, size_t max);
int mbtowc(wchar_t* pwc, const char* pmb, size_t max);
int wctomb(char* pmb, wchar_t wc);

//Macro constants
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define RAND_MAX 32767

#ifdef _cplusplus
}
#endif

#endif
