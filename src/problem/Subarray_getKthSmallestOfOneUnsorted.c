/**
 * 无序数组查找第k小的元素
 *
 * partition and drop
 */

#include <assert.h>
#include <limits.h>

static int partition(int * a, int l, int r) {
    assert(a != NULL);
    assert(l >= 0);
    assert(r >= l);

    int p = l;
    r--;
    while (l < r) {
        while (l < r && a[r] > a[p]) {
            r--;
        }
        while (l < r && a[l] <= a[p]) {
            l++;
        }
        if (l < r) {
            swap(a, l, r);
        }
    }
    if (p != r) {
        swap(a, p, r);
    }
    return r;
}

int Subarray_getKthSmallestOfOneUnsorted(int * a, int n, int k) {
    assert(k >= 0 && k < n);
    int l = 0;
    int r = n;
    int p = -1;
    while ((p = partition(a, 0, r)) != k) {
        if (p < k) {
            k -= p + 1;
            a += p + 1;
            n -= p + 1;
        } else {
            n = p;
        }
    }
    return a[k];
}
