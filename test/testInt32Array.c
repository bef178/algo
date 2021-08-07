#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static
void test_Int32Array_sort5int() {
    printf("testing Int32Array_sort5int ...\n");
    int TIMES = 10000;
    int a[] = { 3, 1, 4, 2, 0 };
    int expected[] = { 0, 1, 2, 3, 4 };
    for (int i = 0; i < TIMES; i++) {
        Int32Array_shuffle(a, 0, 5);
        // Int32Array_print(a, 0, 5);
        Int32Array_sort5int(a, 0, 5);
        assert(Int32Array_equals(expected, 0, 5, a, 0, 5));
    }
}

void testInt32Array() {
    test_Int32Array_sort5int();
}
