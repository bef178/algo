#ifndef _INCLUDED_BYTES
#define _INCLUDED_BYTES

void * mem_pick(int n);

void mem_drop(void * p);

void mem_reset(void * p, int n);

boolean mem_resize(void ** p, int n);

int mem_compare(const byte * p1, int p1size, const byte * p2, int p2size);

void mem_copy(byte * dst, const byte * src, int n);

#endif // _INCLUDED_BYTES
