void Stack_push(Deque * self, int64 value) {
    Deque_pushTail(self, value);
}

int64 Stack_pop(Deque * self) {
    return Deque_pullTail(self);
}

int64 Stack_peek(Deque * self) {
    return Deque_peekTail(self);
}
