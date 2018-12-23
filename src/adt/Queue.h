#ifndef _INCLUDED_QUEUE
#define _INCLUDED_QUEUE

void Queue_enqueue(Deque * self, int64 value);

int64 Queue_dequeue(Deque * self);

int64 Queue_peek(Deque * self);

#endif // _INCLUDED_QUEUE
