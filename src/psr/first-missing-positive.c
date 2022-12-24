/**
 * Given an array of unsorted integers, find the smallest missing positive integer.
 * Must be in O(n) of time and O(1) of space.
 *
 * leetcode #41 hard
 * https://leetcode.com/problems/first-missing-positive/
 */

// like counting sort, any k should be in a[k-1] if sorted and the missing GT k
int firstMissingPositive(int * a, int n) {
    for (int i = 0; i < n; i++) {
        int k = a[i];
        while (k - 1 >= 0 && k - 1 < n && k != a[k - 1]) {
            Int32Array_swap(a, i, k - 1);
            k = a[i];
        }
    }
    for (int i = 0; i < n; i++) {
        if (a[i] != i + 1) {
            return i + 1;
        }
    }
    return n + 1;
}
