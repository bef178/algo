#include <assert.h>
#include <stdlib.h>

typedef struct HashMap {
    Int64_comparef * compareKey;
    Int64_hashf * hashKey;
    int size;
    int numSlots;
    LinkedListNode * slots[0]; // linked list with head node
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

static LinkedListNode * findLowerBound(HashMap * self, int64 key) {
    int32 hashCode = self->hashKey(key);
    int slotIndex = hashCode % self->numSlots;
    if (self->slots[slotIndex] == NULL) {
        self->slots[slotIndex] = LinkedListNode_wrapValue(0);
    }
    LinkedListNode * p = self->slots[slotIndex];
    while (p->next != NULL) {
        MapEntry * entry = (void *) p->next->value;
        if (self->compareKey(entry->key, key) == 0) {
            break;
        }
        p = p->next;
    }
    return p;
}

static void add(LinkedListNode * p, int64 key, int64 value) {
    assert(p->next == NULL);
    MapEntry * entry = MapEntry_wrapValue(key, value);
    LinkedListNode * newNode = LinkedListNode_wrapValue((int64) entry);
    LinkedListNode_insertNext(p, newNode);
}

static int64 get(LinkedListNode * p) {
    assert(p->next != NULL);
    MapEntry * entry = (void *) p->next->value;
    return entry->value;
}

static int64 update(LinkedListNode * p, int64 key, int64 value) {
    assert(p->next != NULL);
    MapEntry * entry = (void *) p->next->value;
    // designated: replace rather than remove then add to tail
    int64 oldValue = entry->value;
    entry->value = value;
    return oldValue;
}

HashMap * HashMap_malloc(int capacity, Int64_comparef * compareKey, Int64_hashf * hashKey) {
    assert(capacity > 0);
    assert(compareKey != NULL);
    capacity = alignCapacity(capacity);
    HashMap * map = calloc(1, sizeof(HashMap) + capacity * sizeof(LinkedListNode *));
    map->compareKey = compareKey;
    map->hashKey = hashKey;
    // expect half full and 2 elements in every linked list in average
    map->numSlots = capacity;
    return map;
}

void HashMap_free(HashMap * self) {
    HashMap_clear(self);
    free(self);
}

void HashMap_clear(HashMap * self) {
    for (int i = 0; i < self->numSlots; i++) {
        if (self->slots[i] != NULL) {
            LinkedListNode * node = self->slots[i];
            while (node != NULL) {
                LinkedListNode * nextNode = node->next;
                MapEntry_free((void *) node->value);
                LinkedListNode_free(node);
                node = nextNode;
            }
            self->slots[i] = NULL;
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
    return HashMap_getOrDefault(self, key, 0);
}

int64 HashMap_getOrDefault(HashMap * self, int64 key, int64 defaultValue) {
    LinkedListNode * p = findLowerBound(self, key);
    if (p->next != NULL) {
        return get(p);
    } else {
        return defaultValue;
    }
}

/**
 * equivalent to:
 *  if (map.contains(key)) {
 *      return map.get(key);
 *  } else {
 *      map.put(key, value);
 *      return value;
 *  }
 */
int64 HashMap_getOrPut(HashMap * self, int64 key, int64 value) {
    LinkedListNode * p = findLowerBound(self, key);
    if (p->next != NULL) {
        return get(p);
    } else {
        add(p, key, value);
        self->size++;
        return value;
    }
}

int64 HashMap_put(HashMap * self, int64 key, int64 value) {
    LinkedListNode * p = findLowerBound(self, key);
    if (p->next != NULL) {
        return update(p, key, value);
    } else {
        add(p, key, value);
        self->size++;
        return 0;
    }
}

int64 HashMap_remove(HashMap * self, int64 key) {
    LinkedListNode * p = findLowerBound(self, key);
    if (p->next != NULL) {
        MapEntry * entry = (void *) LinkedListNode_removeNext(p)->value;
        self->size--;
        int64 oldValue = entry->value;
        MapEntry_free(entry);
        return oldValue;
    }
    return 0;
}

MapIterator * HashMap_mallocIterator(HashMap * self) {
    Iterator * it = Iterator_malloc();
    LinkedListNode * p = it->head;
    for (int i = 0; i < self->numSlots; i++) {
        if (self->slots[i] == NULL) {
            continue;
        }
        LinkedListNode * node = self->slots[i];
        while (node->next != NULL) {
            node = node->next;
            MapEntry * newEntry = MapEntry_copy((void *) node->value);
            LinkedListNode * newNode = LinkedListNode_wrapValue((int64) newEntry);
            LinkedListNode_insertNext(p, newNode);
            p = p->next;
        }
    }
    return it;
}
