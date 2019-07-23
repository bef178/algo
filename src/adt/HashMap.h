#ifndef _INCLUDED_HASHMAP
#define _INCLUDED_HASHMAP

#include "MapIterator.h"

typedef struct HashMap HashMap;

HashMap * HashMap_malloc(int capacity, Int64_comparef * compareKey, Int64_hashf * hashKey);

void HashMap_free(HashMap * self);

void HashMap_clear(HashMap * self);

int HashMap_size(HashMap * self);

boolean HashMap_containsKey(HashMap * self, int64 key);

int64 HashMap_get(HashMap * self, int64 key);

int64 HashMap_getOrDefault(HashMap * self, int64 key, int64 defaultValue);

int64 HashMap_getOrPut(HashMap * self, int64 key, int64 value);

int64 HashMap_put(HashMap * self, int64 key, int64 value);

int64 HashMap_remove(HashMap * self, int64 key);

MapIterator * HashMap_mallocIterator(HashMap *);

#endif // _INCLUDED_HASHMAP
