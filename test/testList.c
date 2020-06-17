#include <assert.h>
#include <stdio.h>

static void testLinkNode() {
    printf("testing LinkNode ...\n");

    int a[] = { 0, 1 };
    LinkNode * p = LinkNode_malloc(a[0]);
    LinkNode * q = LinkNode_malloc(a[1]);
    LinkNode_insertNext(p, q);
    assert(p->next->value == a[1]);
}

void testList() {
    testLinkNode();
}
