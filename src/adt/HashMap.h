#ifndef _INCLUDED_HASHMAP
#define _INCLUDED_HASHMAP

#include "Int64.h"
#include "Iterator.h"
#include "MapEntry.h"

typedef struct HashMap HashMap;

typedef void HashMapIterator;

HashMap * HashMap_malloc(int capacity, Int64_comparef * compareKey, Int64_hashf * hashKey);

void HashMap_free(HashMap * self);

void HashMap_clear(HashMap * self);

int HashMap_size(HashMap * self);

boolean HashMap_containsKey(HashMap * self, int64 key);

void * HashMap_get(HashMap * self, int64 key);

void * HashMap_put(HashMap * self, int64 key, void * value);

void * HashMap_remove(HashMap * self, int64 key);

HashMapIterator * HashMapIterator_malloc(HashMap * self);

boolean HashMapIterator_hasNext(HashMapIterator *);

MapEntry * HashMapIterator_next(HashMapIterator *);

void HashMapIterator_free(HashMapIterator *);

#endif // _INCLUDED_HASHMAP
