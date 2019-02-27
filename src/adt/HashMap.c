#include <assert.h>
#include <stdlib.h>

typedef struct HashMap {
    Int64_comparef * compareKey;
    Int64_hashf * hashKey;
    int size;
    int numSlots;
    ListNode * slots[0]; // linked list with head node
} HashMap;

static int checkCapacity(int requiredCapacity) {
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
    word hashCode = Hash_rehash(self->hashKey(key));
    return self->slots[hashCode % self->numSlots];
}

HashMap * HashMap_malloc(int capacity, Int64_comparef * compareKey, Int64_hashf * hashKey) {
    assert(capacity > 0);
    assert(compareKey != NULL);
    capacity = checkCapacity(capacity);
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

Iterator * HashMapIterator_malloc(HashMap * self) {
    Iterator * it = Iterator_malloc();
    ListNode * p = it->head;
    for (int i = 0; i < self->numSlots; i++) {
        ListNode * node = self->slots[i];
        while (node->next != NULL) {
            node = node->next;
            MapEntry * newEntry = MapEntry_copy((MapEntry *) node->value);
            ListNode * newNode = ListNode_malloc((int64) newEntry);
            ListNode_insertNext(p, newNode);
            p = p->next;
        }
    }
    return it;
}

void HashMapIterator_free(Iterator * it) {
    while (it->head->next != NULL) {
        ListNode * p = ListNode_removeNext(it->head);
        MapEntry * entry = (MapEntry *) p->value;
        MapEntry_free(entry);
        ListNode_free(p);
    }
    Iterator_free(it);
}

boolean HashMapIterator_hasNext(Iterator * it) {
    return Iterator_hasNext(it);
}

MapEntry * HashMapIterator_next(Iterator * it) {
    return (MapEntry *) Iterator_next(it);
}
