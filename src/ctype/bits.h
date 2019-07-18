#ifndef _INCLUDE_BITS
#define _INCLUDE_BITS

int getBit(const void *, int);

void setBit(const void *, int, int);

int32 rotateL(int32 mem, int offset);

int32 rotateR(int32 mem, int offset);

// logical shift (in contrast to arithmetic shift) right
int32 lshiftR(int32 mem, int offset);

#endif // _INCLUDE_BITS
