#ifndef _INCLUDED_HEAP
#define _INCLUDED_HEAP

typedef int (Heap_comparef)(int64, int64);

typedef struct Heap Heap;

Heap * Heap_malloc(int capacity, Heap_comparef * compare);

void Heap_free(Heap * self);

int Heap_capacity(Heap * self);

int Heap_size(Heap * self);

boolean Heap_isEmpty(Heap * self);

void Heap_insert(Heap * self, int64 value);

int64 Heap_remove(Heap * self);

#endif // _INCLUDED_HEAP
