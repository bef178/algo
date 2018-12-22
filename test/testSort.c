#include <stdio.h>

void sysout(int * a, int l, int r) {
    for (int i = 0; i < l; i++) {
        printf(". ");
    }
    for (int i = l; i < r; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void testSingleSort(sort_f * sort, int * a, int l, int r) {
    sysout(a, l, r);
    sort(a, l, r);
    sysout(a, l, r);
}

void testSort() {
    int a[] = {6,5,3,1,8,7,2,4};
    int n = sizeof(a) / sizeof(int);
    testSingleSort(&HeapSort_sort, a, 0, n);
}
