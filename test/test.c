#include <stdio.h>
#include <assert.h>

void ints2stdout(int * a, int l, int r) {
    for (int i = 0; i < l; i++) {
        printf(". ");
    }
    for (int i = l; i < r; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void testSingleSort(sort_f * sort, int * a, int l, int r) {
    ints2stdout(a, l, r);
    sort(a, l, r);
    ints2stdout(a, l, r);
}

void test_sort() {
    int a[] = {6,5,3,1,8,7,2,4};
    int n = sizeof(a) / sizeof(int);
    testSingleSort(&RadixSort_lsd, a, 0, n);
}

void List_toString(List * self) {
    for (int i = 0; i < List_size(self); ++i) {
        void * value = List_get(self, i);
        printf("%d ", *(int *) value);
    }
    printf("\n");
}

void test_ListHead() {
    ListHead * p = ListHead_malloc();
    ListHead * next = ListHead_malloc();

    ListHead_enlinkNext(p, p);
    assert(p->next == p);
    assert(p->prev == p);

    ListHead_insertNext(p, next);
    assert(p->next == next);
    assert(p->prev == next);
    assert(next->next == p);
    assert(next->prev == p);
}

void test_ListNode() {
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

void test_List() {
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


int main() {

    //test_sort();

    test_ListHead();
    test_ListNode();
    test_List();

    return 0;
}
