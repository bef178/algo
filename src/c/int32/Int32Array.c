#include <assert.h>
#include <stdlib.h>
#include <time.h>

int Int32Array_equals(int * a, int l, int r, int * a1, int l1, int r1) {
    assert(a != NULL);
    assert(l >= 0);
    assert(r >= l);
    assert(a1 != NULL);
    assert(l1 >= 0);
    assert(r1 >= l1);

    int n = r - l;
    if (n != r1 - l1) {
        return false;
    }
    a += l;
    a1 += l1;
    for (int i = 0; i < n; i++) {
        if (a[i] != a1[i]) {
            return false;
        }
    }
    return true;
}

int Int32Array_indexOfMax(int * a, int l, int r) {
    int max = l;
    for (int i = l + 1; i < r; i++) {
        if (a[max] < a[i]) {
            max = i;
        }
    }
    return max;
}

int Int32Array_indexOfMin(int * a, int l, int r) {
    int min = l;
    for (int i = l + 1; i < r; i++) {
        if (a[min] > a[i]) {
            min = i;
        }
    }
    return min;
}

void Int32Array_print(int * a, int l, int r) {
    for (int i = l; i < r; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void Int32Array_reverse(int * a, int l, int r) {
    r--;
    while (l < r) {
        Int32Array_swap(a, l++, r--);
    }
}

void Int32Array_shuffle(int * a, int l, int r) {
    assert(a != NULL);
    assert(l >= 0);
    assert(r >= l);

    a += l;
    int n = r - l;

    // srand((unsigned) time(NULL));
    while (n > 0) {
        int i = rand() % n;
        Int32Array_swap(a, i, n - 1);
        n--;
    }
}

void Int32Array_swap(int * a, int i, int j) {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}
