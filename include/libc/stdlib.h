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
//TODO

//Pseudo-random sequence generation
int rand();
void srand(unsigned int seed);

//Dynamic memory allocation
//TODO
//calloc
//free
//malloc
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
