/**
 * Heap
 *
 * since 2009-09-01
 */

#include <stdlib.h>

typedef struct Heap {
    Heap_comparef * compare;
    int capacity;
    int size;
    int64 values[0];
} Heap;

Heap * Heap_malloc(int capacity, Heap_comparef * compare) {
    // assert capacity > 0;
    // assert compare != null;
    Heap * self = calloc(1, sizeof(Heap) + capacity * sizeof(int64));
    self->compare = compare;
    self->capacity = capacity;
    return self;
}

void Heap_free(Heap * self) {
    free(self);
}

static void swapInt64(int64 * a, int i, int j) {
    int64 t = a[i];
    a[i] = a[j];
    a[j] = t;
}

static void filterUp(Heap * self, int index) {
    // assert index >= 0;
    while (index != 0) {
        int t = (index - 1) / 2; // parent
        if (self->compare(self->values[t], self->values[index]) <= 0) {
            break;
        }
        swapInt64(self->values, index, t);
        index = t;
    }
}

static void filterDn(Heap * self, int index) {
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
        swapInt64(self->values, index, t);
        index = t;
    }
}

int Heap_capacity(Heap * self) {
    return self->capacity;
}

int Heap_size(Heap * self) {
    return self->size;
}

boolean Heap_isEmpty(Heap * self) {
    return self->size == 0;
}

void Heap_insert(Heap * self, int64 value) {
    // assert self->size != self->capacity;
    self->values[self->size++] = value;
    filterUp(self, self->size - 1);
}

int64 Heap_remove(Heap * self) {
    // assert self->size != 0;
    int64 value = self->values[0];
    self->values[0] = self->values[--self->size];
    filterDn(self, 0);
    return value;
}
