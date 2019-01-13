#include <assert.h>
#include <stdio.h>

static void sysout(List * self) {
    for (int i = 0; i < List_size(self); ++i) {
        int64 value = List_get(self, i);
        printf("%ld ", value);
    }
    printf("\n");
}

void testListHead() {
    printf("testing ListHead ...\n");

    ListHead * p = ListHead_malloc();

    ListHead_enlinkNext(p, p);
    assert(p->next == p);
    assert(p->prev == p);

    ListHead * next = ListHead_malloc();

    ListHead_insertNext(p, next);
    assert(p->next == next);
    assert(p->prev == next);
    assert(next->next == p);
    assert(next->prev == p);
}

void testListNode() {
    printf("testing ListNode ...\n");

    int a[] = { 0, 1 };
    ListNode * p = ListNode_malloc(a[0]);

    ListNode * next = ListNode_malloc(a[1]);

    ListNode_insertNext(p, next);
    p = p->next;
    assert(p->value == a[1]);
}

void testList() {
    testListHead();
    testListNode();

    printf("testing List ...\n");

    int i = 9;

    List * list = List_malloc();
    List_insert(list, 0, i);

    assert(List_size(list) == 1);
    assert(List_get(list, 0) == 9);

    List_clear(list);

    int values[5];
    for (int i = 0; i < 5; ++i) {
        values[i] = i;
        List_insert(list, 0, values[i]);
    }
    assert(List_size(list) == 5);
    List_remove(list, 3);
    assert(List_get(list, 3) == 0);
}
