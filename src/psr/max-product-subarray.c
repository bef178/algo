/**
 * Given an int array, find the largest product of a contiguous non-empty subsequence of the array
 *
 * leetcode #152 medium
 * https://leetcode.com/problems/maximum-product-subarray/
 */

#include <assert.h>

int maxSubarrayProduct(int * a, int n) {
    assert(a != NULL);
    assert(n > 0);
    int maxProduct = a[0];
    int imax = a[0];
    int imin = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] < 0) {
            int t = imax;
            imax = imin;
            imin = t;
        }
        imax = Int32_max(a[i], imax * a[i]);
        imin = Int32_min(a[i], imin * a[i]);
        maxProduct = Int32_max(maxProduct, imax);
    }
    return imax;
}
