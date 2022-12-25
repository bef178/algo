#include <assert.h>
#include <stdio.h>

static void testLinkedList() {
    printf("testing LinkedList ...\n");

    int a[] = { 0, 1 };
    LinkedListNode * p = LinkedListNode_wrapValue(a[0]);
    LinkedListNode * q = LinkedListNode_wrapValue(a[1]);
    LinkedListNode_insertNext(p, q);
    assert(p->next->value == a[1]);
}

void testList() {
    testLinkedList();
}
