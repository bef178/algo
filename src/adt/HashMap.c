#include <assert.h>
#include <stdlib.h>

typedef struct HashMap {
    Int64_comparef * compareKey;
    Int64_hashf * hashKey;
    int size;
    int numSlots;
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

static ListNode * findLowerBound(HashMap * self, int64 key) {
    int32 hashCode = self->hashKey(key);
    ListNode * p = self->slots[hashCode % self->numSlots];
    while (p->next != NULL) {
        MapEntry * entry = (void *) p->next->value;
        if (self->compareKey(entry->key, key) == 0) {
            break;
        }
        p = p->next;
    }
    return p;
}

HashMap * HashMap_malloc(int capacity, Int64_comparef * compareKey, Int64_hashf * hashKey) {
    assert(capacity > 0);
    assert(compareKey != NULL);
    capacity = alignCapacity(capacity);
    HashMap * map = calloc(1, sizeof(HashMap) + capacity * sizeof(ListNode *));
    map->compareKey = compareKey;
    map->hashKey = hashKey;
    // expect half full and 2 elements in every linked list in average
    map->numSlots = capacity;
    for (int i = 0; i < map->numSlots; i++) {
        map->slots[i] = ListNode_malloc(0);
    }
    return map;
}

void HashMap_free(HashMap * self) {
    HashMap_clear(self);
    for (int i = 0; i < self->numSlots; i++) {
        ListNode_free(self->slots[i]);
    }
    free(self);
}

void HashMap_clear(HashMap * self) {
    for (int i = 0; i < self->numSlots; i++) {
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
    return findLowerBound(self, key)->next != NULL;
}

int64 HashMap_get(HashMap * self, int64 key) {
    ListNode * p = findLowerBound(self, key);
    if (p->next != NULL) {
        MapEntry * entry = (void *) p->next->value;
        return entry->value;
    }
    return 0;
}

int64 HashMap_put(HashMap * self, int64 key, int64 value) {
    ListNode * p = findLowerBound(self, key);
    if (p->next != NULL) {
        MapEntry * entry = (void *) p->next->value;
        // designated: replace rather than remove then add to tail
        int64 oldValue = entry->value;
        entry->value = value;
        return oldValue;
    } else {
        MapEntry * entry = MapEntry_malloc(key, value);
        ListNode * newNode = ListNode_malloc((int64) entry);
        ListNode_insertNext(p, newNode);
        self->size++;
        return 0;
    }
}

int64 HashMap_remove(HashMap * self, int64 key) {
    ListNode * p = findLowerBound(self, key);
    if (p->next != NULL) {
        MapEntry * entry = (void *) ListNode_removeNext(p)->value;
        self->size--;
        int64 oldValue = entry->value;
        MapEntry_free(entry);
        return oldValue;
    }
    return 0;
}

HashMapIterator * HashMapIterator_malloc(HashMap * map) {
    Iterator * it = Iterator_malloc();
    ListNode * p = it->head;
    for (int i = 0; i < map->numSlots; i++) {
        ListNode * node = map->slots[i];
        while (node->next != NULL) {
            node = node->next;
            MapEntry * newEntry = MapEntry_copy((void *) node->value);
            ListNode * newNode = ListNode_malloc((int64) newEntry);
            ListNode_insertNext(p, newNode);
            p = p->next;
        }
    }
    return it;
}

void HashMapIterator_free(HashMapIterator * self) {
    Iterator * it = (Iterator *) self;
    while (it->head->next != NULL) {
        ListNode * p = ListNode_removeNext(it->head);
        MapEntry * entry = (void *) p->value;
        MapEntry_free(entry);
        ListNode_free(p);
    }
    Iterator_free(it);
}

boolean HashMapIterator_hasNext(HashMapIterator * self) {
    return Iterator_hasNext((Iterator *) self);
}

MapEntry * HashMapIterator_next(HashMapIterator * self) {
    return (void *) Iterator_next((Iterator *) self);
}
