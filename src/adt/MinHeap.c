/**
 * MinHeap
 *
 * since 2009-09-01
 */

#include <stdlib.h>

typedef struct MinHeap {
    MinHeap_comparef * compare;
    int capacity;
    int size;
    int64 values[0];
} MinHeap;

MinHeap * MinHeap_malloc(int capacity, MinHeap_comparef * compare) {
    // assert capacity > 0;
    // assert compare != null;
    MinHeap * self = calloc(1, sizeof(MinHeap) + capacity * sizeof(int64));
    self->compare = compare;
    self->capacity = capacity;
    return self;
}

void MinHeap_free(MinHeap * self) {
    free(self);
}

static void filterUp(MinHeap * self, int index) {
    // assert index >= 0;
    while (index != 0) {
        int t = (index - 1) / 2; // parent
        if (self->compare(self->values[t], self->values[index]) <= 0) {
            break;
        }
        int64 value = self->values[index];
        self->values[index] = self->values[t];
        self->values[t] = value;
        index = t;
    }
}

static void filterDn(MinHeap * self, int index) {
    // assert index >= 0;
    while (index < self->size) {
        int i = 2 * index + 1; // l-child
        int j = 2 * index + 2; // r-child

        int t = index;
        if (i < self->size
                && self->compare(self->values[i], self->values[t]) < 0) {
            t = i;
        }
        if (j < self->size
                && self->compare(self->values[j], self->values[t]) < 0) {
            t = j;
        }
        if (t == index) {
            break;
        }
        int64 value = self->values[index];
        self->values[index] = self->values[t];
        self->values[t] = value;
        index = t;
    }
}

int MinHeap_capacity(MinHeap * self) {
    return self->capacity;
}

int MinHeap_size(MinHeap * self) {
    return self->size;
}

boolean MinHeap_isEmpty(MinHeap * self) {
    return self->size == 0;
}

void MinHeap_insert(MinHeap * self, int64 value) {
    // assert self->size != self->capacity;
    // assert value != NULL;
    self->values[self->size++] = value;
    filterUp(self, self->size - 1);
}

int64 MinHeap_remove(MinHeap * self) {
    // assert !MinHeap_isEmpty(self);
    int64 value = self->values[0];
    self->values[0] = self->values[--self->size];
    filterDn(self, 0);
    return value;
}
