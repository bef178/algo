#include <assert.h>
#include <stdio.h>

static void testListHead() {
    printf("testing ListHead ...\n");

    ListHead * p = ListHead_malloc();

    ListHead_enlinkNext(p, p);
    assert(p->next == p);
    assert(p->prev == p);

    ListHead * q = ListHead_malloc();

    ListHead_insertNext(p, q);
    assert(p->next == q);
    assert(p->prev == q);
    assert(q->next == p);
    assert(q->prev == p);

    ListHead * t = ListHead_removeNext(p);
    assert(t == q);
    assert(p->next == p);
}

static void testListNode() {
    printf("testing ListNode ...\n");

    int a[] = { 0, 1 };
    ListNode * p = ListNode_malloc(a[0]);

    ListNode * q = ListNode_malloc(a[1]);

    ListNode_insertNext(p, q);
    p = p->next;
    assert(p->value == a[1]);
}

void testList() {
    testListHead();
    testListNode();
}
