#include <stdio.h>

void ints2stdout(int * a, int l, int r) {
    for (int i = l; i < r; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void test(sort_f * sort, int * a, int l, int r) {
    ints2stdout(a, l, r);
    sort(a, l, r);
    ints2stdout(a, l, r);
}

int main() {
    int a[] = {6,5,3,1,8,7,2,4};
    int n = sizeof(a) / sizeof(int);
    test(&isort1, a, 0, n);
    return 0;
}
