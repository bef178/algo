#ifndef _INCLUDED_HASHMAP
#define _INCLUDED_HASHMAP

typedef struct HashMap HashMap;

typedef int (HashMap_comparef)(int64, int64);

typedef word (HashMap_hashf)(int64);

HashMap * HashMap_malloc(int capacity, HashMap_comparef * compare, HashMap_hashf * hash);

void HashMap_free(HashMap * self);

void HashMap_clear(HashMap * self);

int HashMap_size(HashMap * self);

boolean HashMap_contains(HashMap * self, int64 key);

void * HashMap_get(HashMap * self, int64 key);

void * HashMap_put(HashMap * self, int64 key, void * value);

void * HashMap_remove(HashMap * self, int64 key);

#endif // _INCLUDED_HASHMAP
