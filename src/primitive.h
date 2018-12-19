#ifndef _INCLUDED_PRIMITIVE
#define _INCLUDED_PRIMITIVE

#include <stdint.h>

typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
// #define int int32;

typedef int8_t byte;

#if __WORDSIZE == 32
typedef int32_t word;
#elif __WORDSIZE == 64
typedef int64_t word;
#endif

typedef _Bool boolean;
#define false   (0)
#define true    (1)

typedef float float32;
typedef double float64;
// #define float float32

#define null    ((void *) 0)

#endif /* _INCLUDED_PRIMITIVE */
