#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void printIntArray(const int * a, int l, int r) {
    for (int i = 0; i < l; i++) {
        printf(". ");
    }
    for (int i = l; i < r; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

static int compareInt(const void * a, const void * b) {
  return *(int*)a - *(int*)b;
}

void testSingleSort(sort_f * sort, const int * a, int l, int r) {
    int size = (r - l) * sizeof(int);
    int * dup1 = malloc(size);
    memcpy(dup1, a + l, size);
    int * dup2 = malloc(size);
    memcpy(dup2, a + l, size);
    qsort(dup1, r - l, sizeof(int), &compareInt);
    sort(dup2, l, r);
    assert(memcmp(dup1, dup2, size) == 0);
    free(dup1);
    free(dup2);
}

void testSort() {
    int a[] = {6,5,3,1,8,7,2,4};
    int n = sizeof(a) / sizeof(int);

    printf("testing Sort_bubblesort ...\n");
    testSingleSort(&Sort_bubblesort, a, 0, n);

    printf("testing Sort_countingsort ...\n");
    testSingleSort(&Sort_countingsort, a, 0, n);

    printf("testing Sort_heapsort ...\n");
    testSingleSort(&Sort_heapsort, a, 0, n);

    printf("testing Sort_insertionsort ...\n");
    testSingleSort(&Sort_insertionsort, a, 0, n);
    testSingleSort(&Sort_insertionsort1, a, 0, n);

    printf("testing Sort_mergesort ...\n");
    testSingleSort(&Sort_mergesort, a, 0, n);

    printf("testing Sort_quicksort ...\n");
    testSingleSort(&Sort_quicksort, a, 0, n);

    printf("testing Sort_radixsort ...\n");
    testSingleSort(&Sort_radixsort, a, 0, n);

    printf("testing Sort_radixsort ...\n");
    testSingleSort(&Sort_radixsort, a, 0, n);

    printf("testing Sort_selectionsort ...\n");
    testSingleSort(&Sort_selectionsort, a, 0, n);

    printf("testing Sort_shellsort ...\n");
    testSingleSort(&Sort_shellsort, a, 0, n);
}
