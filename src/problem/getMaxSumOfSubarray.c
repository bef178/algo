/**
 * 最大子段和
 *
 * since 2008-11-18
 */

#include <limits.h>

/**
 * dynamic-programming: O(n)
 */
int getMaxSumOfSubarray_dp(int * a, int l, int r) {
    int sum = INT_MIN;
    int partialSum = INT_MIN;
    for (int i = l; i < r; ++i) {
        if (partialSum >= 0) {
            partialSum += a[i];
        } else {
            partialSum = a[i];
        }
        if (partialSum > sum) {
            sum = partialSum;
        }
    }
    return sum;
}

/**
 * divide-and-conquer: O(n*logn)
 */
int getMaxSumOfSubarray_dc(int * a, int l, int r) {
    if (l > r - 1) {
        return -1;
    } else if (l == r - 1) {
        return a[l] > 0 ? a[l] : 0;
    }

    int sum = 0;
    int m = l + (r - l) / 2;
    {
        int s1 = INT_MIN;
        int partialSum1 = INT_MIN;
        for (int i = m - 1; i >= l; i--) {
            partialSum1 += a[i];
            if (partialSum1 > s1) {
                s1 = partialSum1;
            }
        }

        int s2 = INT_MIN;
        int partialSum2 = INT_MIN;
        for (int i = m; i < r; i++) {
            partialSum2 += a[i];
            if (partialSum2 > s2) {
                s2 = partialSum2;
            }
        }

        sum = s1 + s2;
    }

    int sumL = getMaxSumOfSubarray_dc(a, l, m);
    if (sumL > sum) {
        sum = sumL;
    }

    int sumR = getMaxSumOfSubarray_dc(a, m, r);
    if (sumR > sum) {
        sum = sumR;
    }

    return sum;
}
