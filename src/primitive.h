#ifndef _INCLUDED_PRIMITIVE
#define _INCLUDED_PRIMITIVE

#include <stdint.h>

typedef int8_t byte;

typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
// #define int int32;

// 每种类型应该描述自身的特征，而size_t描述了用途，弃之

typedef _Bool boolean;
#define false   (0)
#define true    (1)

typedef float float32;
typedef double float64;
// #define float float32

#define null    ((void *) 0)

#endif /* _INCLUDED_PRIMITIVE */
