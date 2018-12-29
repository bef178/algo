#ifndef _INCLUDED_COMBINE
#define _INCLUDED_COMBINE

int Combine_calculate(int n, int m);

int Combine_nextIndex(int index);

int Combine_toBytes(byte * alphabet, int n, int index, byte * dst);

int Combine_toIndex(byte * alphabet, int n, byte * src, int m);

void Combine_printAll(byte * alphabet, int n, int m);

#endif
