#include <assert.h>
#include <stdio.h>
#include <string.h>

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

void testSubarrayRemoveByte() {
    printf("testing Subarray_removeByte ...\n");
    byte actual[] = "the quick brown fox jumps over the lazy dog";
    byte * expected = "th qck brwn fx jmps vr th lz dg";
    int n = Subarray_removeByte(actual, "aeiouy");
    assert(n == strlen(expected));
    assert(strncmp(actual, expected, n) == 0);
}
