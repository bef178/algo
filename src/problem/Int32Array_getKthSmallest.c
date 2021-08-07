/**
 * 无序数组查找第k小的元素
 *
 * leetcode#215
 * https://leetcode.com/problems/kth-largest-element-in-an-array/
 */

#include <assert.h>

static
int partition(int * a, int l, int r) {
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
            Int32Array_swap(a, l, r);
        }
    }
    if (p != r) {
        Int32Array_swap(a, p, r);
    }
    return r;
}

int Int32Array_getKthSmallest(int * a, int l, int r, int k) {
    assert(a != NULL);
    assert(l >= 0);
    assert(r >= l);
    assert(k >= 0 && k < r - l);
    a += l;
    int n = r - l;
    int p = -1;
    while ((p = partition(a, 0, n)) != k) {
        if (p < k) {
            a += p + 1;
            n -= p + 1;
            k -= p + 1;
        } else {
            n = p;
        }
    }
    return a[k];
}
