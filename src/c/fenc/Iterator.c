#include <assert.h>
#include <stdlib.h>

Iterator * Iterator_malloc() {
    Iterator * self = calloc(1, sizeof(Iterator));
    self->head = LinkedListNode_malloc(0);
    self->current = self->head;
    return self;
}

void Iterator_free(Iterator * self) {
    assert(self != NULL);
    assert(self->head != NULL);
    while (self->head->next != NULL) {
        LinkedListNode * p = LinkedListNode_removeNext(self->head);
        LinkedListNode_free(p);
    }
    LinkedListNode_free(self->head);
    self->head = NULL;
    free(self);
    self = NULL;
}

boolean Iterator_hasNext(Iterator * self) {
    assert(self != NULL);
    assert(self->current != NULL);
    return self->current->next != NULL;
}

int64 Iterator_next(Iterator * self) {
    self->current = self->current->next;
    return self->current->value;
}
