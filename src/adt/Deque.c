/**
 * 双端循环队列(数组)
 * head: 如果队非空，则从这里出队；总是指向一个有值的slot
 * tail = head + size: 如果队非满，则从这里入队；总是指向一个无值的slot
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct Deque {
    int capacity;
    int size;
    int head;
    int64 slots[0];
} Deque;

Deque * Deque_malloc() {
    const int capacity = 64;
    Deque * p = calloc(1, sizeof(Deque) + capacity * sizeof(int64));
    p->capacity = capacity;
    return p;
}

void Deque_free(Deque * self) {
    free(self);
}

int Deque_size(Deque * self) {
    return self->size;
}

boolean Deque_isEmpty(Deque * self) {
    return self->size == 0;
}

void Deque_clear(Deque * self) {
    int capacity = self->capacity;
    memset(self, 0, sizeof(Deque) + capacity * sizeof(int64));
    self->capacity = capacity;
}

int Deque_capacity(Deque * self) {
    return self->capacity;
}

void Deque_pushHead(Deque * self, int64 value) {
    assert(self->size + 1 < self->capacity);
    if (self->size > 0) {
        self->head--;
        if (self->head < 0) {
            self->head += self->capacity;
        }
    }
    self->slots[self->head] = value;
    self->size++;
}

void Deque_pushTail(Deque * self, int64 value) {
    assert(self->size + 1 < self->capacity);
    int tail = self->head + self->size;
    if (tail >= self->capacity) {
        tail -= self->capacity;
    }
    self->slots[tail] = value;
    self->size++;
}

int64 Deque_pullHead(Deque * self) {
    assert(self->size > 0);
    int64 value = self->slots[self->head];
    self->slots[self->head] = 0;
    self->head++;
    if (self->head >= self->capacity) {
        self->head -= self->capacity;
    }
    self->size--;
    return value;
}

int64 Deque_pullTail(Deque * self) {
    assert(self->size > 0);
    int tail = self->head + self->size - 1;
    if (tail >= self->capacity) {
        tail -= self->capacity;
    }
    int64 value = self->slots[tail];
    self->slots[tail] = 0;
    self->size--;
    return value;
}

int64 Deque_peekHead(Deque * self) {
    assert(self->size > 0);
    return self->slots[self->head];
}

int64 Deque_peekTail(Deque * self) {
    assert(self->size > 0);
    int tail = self->head + self->size - 1;
    if (tail >= self->capacity) {
        tail -= self->capacity;
    }
    return self->slots[tail];
}
