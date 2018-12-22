#include <stdlib.h>

typedef struct ListNode {
    ListHead link;
    int64 value;
} ListNode;

ListNode * ListNode_malloc(int64 value) {
    ListNode * p = calloc(1, sizeof(ListNode));
    p->value = value;
    return p;
}

void ListNode_free(ListNode * self) {
    free(self);
}

static ListNode * fromLink(ListHead * p) {
    return p == NULL
        ? NULL
        : GET_CONTAINER(ListNode, link, p);
}

// think: delegate to link api to ListHead
ListNode * ListNode_delinkNext(ListNode * self) {
    ListHead * p = ListHead_delinkNext(&self->link);
    return fromLink(p);
}

void ListNode_enlinkNext(ListNode * self, ListNode * futureNext) {
    ListHead_enlinkNext(&self->link, &futureNext->link);
}

void ListNode_insertNext(ListNode * self, ListNode * futureNext) {
    // assert futureNext != null;
    ListHead_insertNext(&self->link, &futureNext->link);
}

ListNode * ListNode_removeNext(ListNode * self) {
    ListHead * p = ListHead_removeNext(&self->link);
    return fromLink(p);
}

ListNode * ListNode_offset(ListNode * self, int offset) {
    ListHead * p = ListHead_offset(&self->link, offset);
    return fromLink(p);
}

int64 ListNode_get(ListNode * self) {
    return self->value;
}

void ListNode_set(ListNode * self, int64 value) {
    self->value = value;
}
