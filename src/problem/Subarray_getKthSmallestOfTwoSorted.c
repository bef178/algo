/**
 * 两个有序数组查找第k小的元素
 */

#include <assert.h>
#include <limits.h>

int Subarray_getKthSmallestOfTwoSorted(int * a1, int n1, int * a2, int n2, int k) {
    assert(a1 != NULL && n1 >= 0);
    // assert a1 is sorted
    assert(a2 != NULL && n2 >= 0);
    // assert a2 is sorted
    assert(k >= 0 && k < n1 + n2);

    int i1 = 0;
    int i2 = 0;
    while (true) {
        if (i1 == n1) {
            return a2[i2 + k];
        }
        if (i2 == n2) {
            return a1[i1 + k];
        }
        if (k == 0) {
            return a1[i1] < a2[i2] ? a1[i1] : a2[i2];
        }

        int d = (k + 1) / 2; // size to drop

        int j1 = i1 + d - 1;
        int v1 = j1 >= n1 ? INT_MAX : a1[j1]; // out of bounds

        int j2 = i2 + d - 1;
        int v2 = j2 >= n2 ? INT_MAX : a2[j2];

        if (v1 < v2) {
            i1 += d;
        } else {
            i2 += d;
        }
        k -= d;
    }
}
