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
int getAvailable(byte * alphabet, int n, byte * used, int j) {
    for (int i = 0; i < n; i++) {
        if (used[i] == 1) {
            continue;
        }
        if (j == 0) {
            used[i] = 1;
            return alphabet[i];
        } else {
            j--;
        }
    }
    assert(false);
}

/**
 * Given alphabet and index, find the permutation
 *
 * leetcode #60. Permutation Sequence
 */
public
void Permutation_getByIndex(byte * alphabet, int n, int index, byte * dst) {
    byte * used = calloc(n, sizeof(byte));
    for (int i = 0; i < n; i++) {
        int fi = getFactorial(n - 1 - i);
        int j = index / fi;
        dst[i] = getAvailable(alphabet, n, used, j);
        index -= j * fi;
    }
}
