#include <assert.h>
#include <stdlib.h>

public
LinkedListNode * LinkedListNode_malloc() {
    LinkedListNode * node = calloc(1, sizeof(LinkedListNode));
    node->value = 0;
    return node;
}

public
LinkedListNode * LinkedListNode_wrapValue(int64 value) {
    LinkedListNode * node = LinkedListNode_malloc();
    node->value = value;
    return node;
}

public
int64 LinkedListNode_free(LinkedListNode * self) {
    int64 value = self->value;
    free(self);
    return value;
}

/**
 * concat/join
 */
public
void LinkedListNode_enlinkNext(LinkedListNode * self, LinkedListNode * futureNext) {
    self->next = futureNext;
    if (futureNext != NULL) {
        futureNext->prev = self;
    }
}

public
LinkedListNode * LinkedListNode_delinkNext(LinkedListNode * self) {
    LinkedListNode * p = self->next;
    if (p != NULL) {
        self->next = NULL;
        p->prev = NULL;
    }
    return p;
}

public
void LinkedListNode_enlinkPrev(LinkedListNode * self, LinkedListNode * futurePrev) {
    self->prev = futurePrev;
    if (futurePrev != NULL) {
        futurePrev->next = self;
    }
}

public
LinkedListNode * LinkedListNode_delinkPrev(LinkedListNode * self) {
    LinkedListNode * p = self->prev;
    if (p != NULL) {
        self->prev = NULL;
        p->next = NULL;
    }
    return p;
}

public
void LinkedListNode_insertNext(LinkedListNode * self, LinkedListNode * futureNext) {
    assert(futureNext != NULL);
    LinkedListNode * p = LinkedListNode_delinkNext(self);
    LinkedListNode_enlinkNext(self, futureNext);
    LinkedListNode_enlinkNext(futureNext, p);
}

public
LinkedListNode * LinkedListNode_removeNext(LinkedListNode * self) {
    LinkedListNode * p = LinkedListNode_delinkNext(self);
    if (p != NULL) {
        LinkedListNode_enlinkNext(self, LinkedListNode_delinkNext(p));
    }
    return p;
}
