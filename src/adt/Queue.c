void Queue_enqueue(Deque * self, int64 value) {
    Deque_pushTail(self, value);
}

int64 Queue_dequeue(Deque * self) {
    return Deque_pullHead(self);
}

int64 Queue_peek(Deque * self) {
    return Deque_peekHead(self);
}
