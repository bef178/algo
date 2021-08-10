#include <assert.h>
#include <stdlib.h>

typedef struct LinkedList {
    LinkedListNode * head;
} LinkedList;

LinkedList * LinkedList_malloc() {
    LinkedListNode * head = LinkedListNode_malloc();
    LinkedListNode_enlinkNext(head, head);
    LinkedList * list = calloc(1, sizeof(LinkedList));
    list->head = head;
    return list;
}

void LinkedList_free(LinkedList * self) {
    while (!LinkedList_isEmpty(self)) {
        LinkedList_remove(self);
    }
    LinkedListNode_free(self->head);
    self->head = NULL;
    free(self);
}

void LinkedList_insert(LinkedList * self, int64 value) {
    LinkedListNode * node = LinkedListNode_wrapValue(value);
    LinkedListNode_insertNext(self->head->prev, node);
}

void LinkedList_insertAtIndex(LinkedList * self, int index, int64 value) {
    assert(index >= 0 && index < LinkedList_size(self));
    LinkedListNode * p = self->head;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }
    LinkedListNode_insertNext(p, LinkedListNode_wrapValue(value));
}

boolean LinkedList_isEmpty(LinkedList * self) {
    return self->head->next != self->head;
}

// remove the last element
int64 LinkedList_remove(LinkedList * self) {
    assert(!LinkedList_isEmpty(self));
    LinkedListNode * node = self->head->prev;
    LinkedListNode_removeNext(node->prev);
    return LinkedListNode_free(node);
}

int LinkedList_size(LinkedList * self) {
    LinkedListNode * p = self->head;
    int n = 0;
    while (p->next != self->head) {
        n++;
    }
    return n;
}
