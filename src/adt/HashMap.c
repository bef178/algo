#include <assert.h>
#include <stdlib.h>

#include "MapEntry.h"

typedef struct HashMap {
    Int64_comparef * compareKey;
    int capacity;
    int size;
    ListNode * slots[0]; // linked list with head node
} HashMap;

static int alignCapacity(int requiredCapacity) {
    const int MAX = ~(-1U >> 1) >> 1; // 1 << ((sizeof(int32) << 3) - 2);
    const int MIN = 1 << 6; // 64
    if (requiredCapacity <= MIN) {
        return MIN;
    } else if (requiredCapacity >= MAX) {
        return MAX;
    }
    int capacity = MIN;
    while (capacity < requiredCapacity) {
        capacity <<= 1;
    }
    return capacity;
}

static ListNode * findSlot(HashMap * self, int64 key) {
    int64 hashCode = rehash(key);
    return self->slots[hashCode % self->capacity];
}

HashMap * HashMap_malloc(int capacity, Int64_comparef * compareKey) {
    assert(capacity > 0);
    assert(compareKey != NULL);
    capacity = alignCapacity(capacity);
    HashMap * map = calloc(1, sizeof(HashMap) + capacity * sizeof(ListNode *));
    map->compareKey = compareKey;
    map->capacity = capacity;
    for (int i = 0; i < map->capacity; i++) {
        map->slots[i] = ListNode_malloc(0);
    }
    return map;
}

void HashMap_free(HashMap * self) {
    HashMap_clear(self);
    for (int i = 0; i < self->capacity; i++) {
        ListNode_free(self->slots[i]);
    }
    free(self);
}

void HashMap_clear(HashMap * self) {
    for (int i = 0; i < self->capacity; i++) {
        ListNode * node = ListNode_delinkNext(self->slots[i]);
        while (node != NULL) {
            ListNode * p = node->next;
            MapEntry * entry = (void *) node->value;
            MapEntry_free(entry);
            node = p;
        }
    }
    self->size = 0;
}

int HashMap_size(HashMap * self) {
    return self->size;
}

boolean HashMap_containsKey(HashMap * self, int64 key) {
    return HashMap_get(self, key) != NULL;
}

void * HashMap_get(HashMap * self, int64 key) {
    ListNode * node = findSlot(self, key)->next;
    while (node != NULL) {
        MapEntry * entry = (void *) node->value;
        if (self->compareKey(entry->key, key) == 0) {
            return entry->value;
        }
        node = node->next;
    }
    return NULL;
}

void * HashMap_put(HashMap * self, int64 key, void * value) {
    assert(value != NULL);
    ListNode * node = findSlot(self, key);
    while (node->next != NULL) {
        ListNode * p = node->next;
        MapEntry * entry = (void *) p->value;
        if (self->compareKey(entry->key, key) == 0) {
            // designated: replace rather than remove then add to tail
            void * oldValue = entry->value;
            entry->value = value;
            return oldValue;
        }
        node = node->next;
    }
    ListNode * newNode = ListNode_malloc((int64) MapEntry_malloc(key, value));
    ListNode_insertNext(node, newNode);
    self->size++;
    return NULL;
}

void * HashMap_remove(HashMap * self, int64 key) {
    ListNode * node = findSlot(self, key);
    while (node->next != NULL) {
        ListNode * p = node->next;
        MapEntry * entry = (void *) p->value;
        if (self->compareKey(entry->key, key) == 0) {
            ListNode_removeNext(node);
            self->size--;
            void * oldValue = entry->value;
            MapEntry_free(entry);
            return oldValue;
        }
    }
    return NULL;
}
