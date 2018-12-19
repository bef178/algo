/**
 * List works base on index
 * accepting only non-null value
 */

#include <stdlib.h>

ListNode * ListNode_malloc() {
    return calloc(1, sizeof(ListNode));
}

void ListNode_free(ListNode * self) {
    free(self);
}

ListNode * ListNode_fromListHead(ListHead * p) {
    return p == NULL
        ? NULL
        : GET_CONTAINER(ListNode, linkage, p);
}

ListNode * ListNode_offset(ListNode * self, int offset) {
    ListHead * p = ListHead_offset(&self->linkage, offset);
    return ListNode_fromListHead(p);
}
