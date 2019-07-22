#ifndef _INCLUDE_CMEMORY
#define _INCLUDE_CMEMORY

int32 hash_bkdr(const byte * p, const int n);
int32 hash_djb(const byte * p, const int n);

void setSingleBit(const void * stream, int offset, boolean value);
boolean testSingleBit(const void * stream, int offset);

#endif // _INCLUDE_CMEMORY
