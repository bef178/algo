#include <stdlib.h>

#include "ListHead.h"

/**
 * internally delegate ListNode to ListHead
 */
static ListNode * fromListHead(ListHead * p) {
    return (ListNode *) (p - 0);
}

static ListHead * toListHead(ListNode * p) {
    return (ListHead *) (p + 0);
}

ListNode * ListNode_malloc(int64 value) {
    ListNode * node = calloc(1, sizeof(ListNode));
    node->value = value;
    return node;
}

void ListNode_free(ListNode * self) {
    free(self);
}

void ListNode_enlinkNext(ListNode * self, ListNode * futureNext) {
    ListHead_enlinkNext(toListHead(self), toListHead(futureNext));
}

ListNode * ListNode_delinkNext(ListNode * self) {
    ListHead * p = ListHead_delinkNext(toListHead(self));
    return fromListHead(p);
}

void ListNode_insertNext(ListNode * self, ListNode * futureNext) {
    ListHead_insertNext(toListHead(self), toListHead(futureNext));
}

ListNode * ListNode_removeNext(ListNode * self) {
    ListHead * p = ListHead_removeNext(toListHead(self));
    return fromListHead(p);
}
