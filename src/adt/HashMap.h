#ifndef _INCLUDED_HASHMAP
#define _INCLUDED_HASHMAP

#include "Iterator.h"
#include "MapEntry.h"

typedef struct HashMap HashMap;

typedef void HashMapIterator;

HashMap * HashMap_malloc(int capacity, Int64_comparef * compareKey, Int64_hashf * hashKey);

void HashMap_free(HashMap * self);

void HashMap_clear(HashMap * self);

int HashMap_size(HashMap * self);

boolean HashMap_containsKey(HashMap * self, int64 key);

int64 HashMap_get(HashMap * self, int64 key);

int64 HashMap_put(HashMap * self, int64 key, int64 value);

int64 HashMap_remove(HashMap * self, int64 key);

HashMapIterator * HashMapIterator_malloc(HashMap *);

boolean HashMapIterator_hasNext(HashMapIterator *);

MapEntry * HashMapIterator_next(HashMapIterator *);

void HashMapIterator_free(HashMapIterator *);

#endif // _INCLUDED_HASHMAP
