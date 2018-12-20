#include <assert.h>
#include <stdio.h>

static void sysout(List * self) {
    for (int i = 0; i < List_size(self); ++i) {
        void * value = List_get(self, i);
        printf("%d ", *(int *) value);
    }
    printf("\n");
}

void testListHead() {
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
    int a[] = { 0, 1 };
    ListNode * p = ListNode_malloc();
    p->value = a + 0;

    assert(ListNode_fromListHead(&(p->linkage)) == p);

    ListNode * next = ListNode_malloc();
    next->value = a + 1;

    ListHead_insertNext(&p->linkage, &next->linkage);
    assert(p->linkage.next == &next->linkage);
    assert(ListNode_fromListHead(p->linkage.next) == next);
}

void testList() {
    testListHead();
    testListNode();

    int i = 9;

    List * list = List_malloc();
    List_insert(list, 0, &i);

    assert(List_size(list) == 1);
    assert(*(int *) List_get(list, 0) == 9);

    List_clear(list);

    int values[5];
    for (int i = 0; i < 5; ++i) {
        values[i] = i;
        List_insert(list, 0, values + i);
    }
    assert(List_size(list) == 5);
    List_remove(list, 3);
    assert(*(int *) List_get(list, 3) == 0);
}
