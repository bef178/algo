#include <stdio.h>

void ints2stdout(int * a, int l, int r) {
    for (int i = 0; i < l; i++) {
        printf(". ");
    }
    for (int i = l; i < r; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void swap(int * a, int i, int j) {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

int min(int i, int j) {
    return i <= j ? i : j;
}

int max(int i, int j) {
    return i >= j ? i : j;
}
