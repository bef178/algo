/**
 * Given the charset and the index, find the permutation
 *
 * leetcode #60 hard
 * https://leetcode.com/problems/permutation-sequence/
 */

#include <assert.h>
#include <stdlib.h>

static
int getFactorial(int n) {
    int p = 1;
    while (n > 0) {
        p *= n--;
    }
    return p;
}

static
int getAvailable(byte * charset, int n, boolean * used, int j) {
    for (int i = 0; i < n; i++) {
        if (used[i]) {
            continue;
        }
        if (j == 0) {
            used[i] = true;
            return charset[i];
        } else {
            j--;
        }
    }
    assert(false);
}

public
void findPermutationByIndex(byte * charset, int n, int index, byte * dst) {
    boolean * used = calloc(n, sizeof(boolean));
    for (int i = 0; i < n; i++) {
        int fi = getFactorial(n - 1 - i);
        int j = index / fi;
        dst[i] = getAvailable(charset, n, used, j);
        index -= j * fi;
    }
    free(used);
}
