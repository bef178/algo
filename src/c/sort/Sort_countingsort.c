#include <memory.h>

/**
 * non-comparion sort, apply to keys that are small integers
 */
void Sort_countingsort(int * a, int l, int r) {
    int maxKey = a[Int32Array_indexOfMax(a, l, r)];
    int minKey = a[Int32Array_indexOfMin(a, l, r)];

    int cLength = maxKey - minKey + 1;
    int c[cLength];
    memset(c, 0, sizeof(c));
    for (int i = l; i < r; i++) {
        c[a[i] - minKey]++;
    }

    // find the positions
    for (int i = 1; i < cLength; i++) {
        c[i] += c[i - 1];
    }

    int a1[r - l];
    for (int i = r - 1; i >= l; i--) {
        a1[--c[a[i] - minKey]] = a[i];
    }

    for (int i = 0; i < r; i++) {
        a[i + l] = a1[i];
    }
}
