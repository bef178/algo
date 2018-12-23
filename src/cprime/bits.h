#ifndef _INCLUDE_BITS
#define _INCLUDE_BITS

#define GET_BITS(flags, f)      ((flags) & (f))
#define SET_BITS(flags, f)      do { (flags) |= (f); } while(0)
#define CLEAR_BITS(flags, f)    do { (flags) &= ~(f); } while(0)

/**
 * get 1 bit from @stream, indicated by @offset
 * returns target bit
 */
int getBit(const byte * stream, int offset);

void setBit(byte * stream, int offset);

void clearBit(byte * stream, int offset);

int32 rotateL(int32 mem, int offset);

int32 rotateR(int32 mem, int offset);

// logical (in contrast to arithmetic) shift right
int32 lshiftR(int32 mem, int offset);

#endif // _INCLUDE_BITS
