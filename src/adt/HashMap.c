#include <stdlib.h>

#include "List.h"
#include "MapEntry.h"

typedef struct HashMap {
    HashMap_comparef * compareKey;
    HashMap_hashf * hashKey;
    int capacity;
    int size;
    List * slots[0];
} HashMap;

static int alignCapacity(int requiredCapacity) {
    static const int MAX_CAPACITY = ~(-1U >> 1);
    if (requiredCapacity < 16) {
        return 16;
    } else if (requiredCapacity > MAX_CAPACITY) {
        return MAX_CAPACITY;
    }
    int capacity = 16;
    while (capacity < requiredCapacity) {
        capacity <<= 1;
    }
    return capacity;
}

static List * findSlot(HashMap * self, int64 key) {
    word hashCode = self->hashKey(key);
    hashCode = rehash(hashCode) & (self->capacity - 1);
    return self->slots[hashCode];
}

HashMap * HashMap_malloc(int capacity, HashMap_comparef * compareKey, HashMap_hashf * hashKey) {
    // assert capacity > 0;
    capacity = alignCapacity(capacity);
    HashMap * map = calloc(1, sizeof(HashMap) + capacity * sizeof(List *));
    map->compareKey = compareKey;
    map->hashKey = hashKey;
    map->capacity = capacity;
    for (int i = 0; i < capacity; i++) {
        map->slots[i] = List_malloc();
    }
    return map;
}

void HashMap_free(HashMap * self) {
    HashMap_clear(self);
    for (int i = 0; i < self->capacity; i++) {
        List_free(self->slots[i]);
    }
    free(self);
}

void HashMap_clear(HashMap * self) {
    for (int i = 0; i < self->capacity; i++) {
        List * slot = self->slots[i];
        while (!List_isEmpty(slot)) {
            MapEntry * entry = (void *) List_remove(slot, 0);
            MapEntry_free(entry);
        }
    }
}

int HashMap_size(HashMap * self) {
    return self->size;
}

boolean HashMap_contains(HashMap * self, int64 key) {
    List * slot = findSlot(self, key);
    for (int i = 0; i < List_size(slot); i++) {
        MapEntry * entry = (void *) List_get(slot, i);
        if (self->compareKey(entry->key, key) == 0) {
            return true;
        }
    }
    return false;
}

void * HashMap_get(HashMap * self, int64 key) {
    List * slot = findSlot(self, key);
    for (int i = 0; i < List_size(slot); i++) {
        MapEntry * entry = (void *) List_get(slot, i);
        if (self->compareKey(entry->key, key) == 0) {
            return entry->value;
        }
    }
    return NULL;
}

void * HashMap_put(HashMap * self, int64 key, void * value) {
    // assert value != null;
    List * slot = findSlot(self, key);
    for (int i = 0; i < List_size(slot); i++) {
        MapEntry * entry = (void *) List_get(slot, i);
        if (self->compareKey(entry->key, key) == 0) {
            void * old = entry->value;
            entry->value = old;
            return old;
        }
    }
    List_insert(slot, -1, (int64) MapEntry_malloc(key, value));
    self->size++;
    return NULL;
}

void * HashMap_remove(HashMap * self, int64 key) {
    // assert key != NULL;
    List * slot = findSlot(self, key);
    for (int i = 0; i < List_size(slot); i++) {
        MapEntry * entry = (void *) List_get(slot, i);
        if (self->compareKey(entry->key, key) == 0) {
            List_remove(slot, i);
            self->size--;
            void * value = entry->value;
            MapEntry_free(entry);
            return value;
        }
    }
    return NULL;
}
