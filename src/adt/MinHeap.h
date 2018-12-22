#ifndef _INCLUDED_MINHEAP
#define _INCLUDED_MINHEAP

typedef int (MinHeap_comparef)(int64, int64);

typedef struct MinHeap MinHeap;

MinHeap * MinHeap_malloc(int capacity, MinHeap_comparef * compare);

void MinHeap_free(MinHeap * self);

int MinHeap_capacity(MinHeap * self);

int MinHeap_size(MinHeap * self);

boolean MinHeap_isEmpty(MinHeap * self);

void MinHeap_insert(MinHeap * self, int64 value);

int64 MinHeap_remove(MinHeap * self);

#endif // _INCLUDED_MINHEAP
