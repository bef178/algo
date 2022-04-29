/**
 * Given an array of integers `a`, remove all occurrences of `ex` and compact `a`.
 * Return the length of the "new" array.
 * Must O(1) in space.
 *
 * leetcode #27 easy
 * https://leetcode.com/problems/remove-element/
 */

#include <assert.h>

int removeElement(int * a, int l, int r, int ex) {
    assert(a != NULL);
    assert(l >= 0);
    assert(r >= l);
    int k = l;
    while (k < r && a[k] != ex) {
        k++;
    }
    for (int i = k + 1; i < r; i++) {
        if (a[i] == ex) {
            continue;
        }
        a[k++] = a[i];
    }
    return k - l;
}
