#include <assert.h>

// 2-way merge sort, stable, not in-place, average O(n\log_2 n), worst O(n\log_2 n)
interface
void Sort_mergesort(int * a, int l, int r) {
    assert(a != null);
    assert(l >= 0);
    assert(r >= l);

    if (r - l <= 1) {
        // 0 or 1 element
        return;
    }

    int m = l + (r - l) / 2;
    Sort_mergesort(a, l, m);
    Sort_mergesort(a, m, r);

    int a1[r - l]; // buffer for intermediate result
    int i = l;
    int j = m;
    int k = 0;
    while (i < m && j < r) {
        a1[k++] = a[i] <= a[j]
            ? a[i++]
            : a[j++];
    }
    while (i < m) {
        a1[k++] = a[i++];
    }
    while (j < r) {
        a1[k++] = a[j++];
    }
    for (i = l, k = 0; i < r; i++, k++) {
        a[i] = a1[k];
    }
}
