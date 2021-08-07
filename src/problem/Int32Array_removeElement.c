#include <assert.h>
#include <string.h>

/**
 * leetcode#27
 * https://leetcode.com/problems/remove-element/
 */
int Int32Array_removeElement(int * a, int l, int r, int ex) {
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

/**
 * remove any ch in @targets from string
 * return the new length of string
 * O(n)
 */
int Subarray_removeByte(byte * s, byte * targets) {
    boolean map[128] = { false };
    int n = strlen(targets);
    for (int i = 0; i < n; i++) {
        map[targets[i]] = true;
    }

    byte * p = s;
    byte * q = NULL;
    while (*p != NUL) {
        if (map[*p]) {
            if (q == NULL) {
                q = p;
            }
        } else {
            if (q != NULL) {
                *q++ = *p;
            }
        }
        p++;
    }
    *q = NUL;
    return q - s;
}
