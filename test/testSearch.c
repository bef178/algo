#include <assert.h>

void testSearch() {
    printf("testing BinarySearch ...\n");
    int a[] = { 1, 3, 5, 6, 6, 6, 6, 7, 8, 9 };
    int n = sizeof(a) / sizeof(int);
    int i = BinarySearch_firstMeet(a, 0, n, 5);
    assert(i == 2);

    i = BinarySearch_lowerBound(a, 0, n, 6);
    assert(i == 3);

    i = BinarySearch_upperBound(a, 0, n, 6);
    assert(i == 7);
}
