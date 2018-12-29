#ifndef _INCLUDED_DEQUE
#define _INCLUDED_DEQUE

/**
 * double-ended queue
 */

typedef struct Deque Deque;

Deque * Deque_malloc();

void Deque_free(Deque * self);

int Deque_size(Deque * self);

boolean Deque_isEmpty(Deque * self);

void Deque_clear(Deque * self);

int64 Deque_get(Deque * self, int i);

int Deque_capacity(Deque * self);

void Deque_pushHead(Deque * self, int64 value);

void Deque_pushTail(Deque * self, int64 value);

int64 Deque_pullHead(Deque * self);

int64 Deque_pullTail(Deque * self);

int64 Deque_peekHead(Deque * self);

int64 Deque_peekTail(Deque * self);

#endif // _INCLUDED_DEQUE
