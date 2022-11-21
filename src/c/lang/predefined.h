#ifndef _INCLUDED_PREDEFINED
#define _INCLUDED_PREDEFINED

#include <stdint.h>

typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef int8_t byte;

typedef _Bool boolean;
#define false (!!0)
#define true (!false)

typedef float float32;
typedef double float64;

// null pointer
#define null ((void *) 0)

#define public
#define interface
#define internal

#endif
