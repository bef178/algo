/**
 * KMP (Knuth Morris Pratt) pattern searching
 *
 * implementation since 2008-01-30
 */

// i |  0  1  2  3  4  5  6  7  8  |  0  1  2  3  4 |
// p |  a  b  a  a  b  c  a  b  a  |  a  a  a  b  c |
// r | -1  0 -1  1  0  2 -1  0 -1  | -1 -1 -1  2  0 |

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static int * Kmp_revise(const byte * p, const int pSize) {
    assert(p != NULL);
    assert(pSize > 0);

    int * r = calloc(pSize, sizeof(int));
    if (r == NULL) {
        perror("E: out of memory");
        exit(1);
    }

    int k = -1;
    r[0] = -1;
    for (int i = 1; i < pSize; i++) {
        if (k != -1 && p[i - 1] != p[k]) {
            k = r[k];
        }
        ++k;
        if (p[i] == p[k]) {
            r[i] = r[k];
        } else {
            r[i] = k;
        }
    }

    return r;
}

/**
 * strstr()'s interface
 */
byte * Kmp_find(byte * s, int sSize, const byte * p, int pSize) {
    assert(s != NULL);
    assert(sSize >= 0);
    assert(p != NULL);
    assert(pSize >= 0);

    if (pSize == 0) {
        return s;
    } else if (sSize == 0) {
        return NULL;
    }

    int * r = Kmp_revise(p, pSize);
    byte * q = NULL;

    int i = 0;
    int j = 0;
    while (i < sSize) {
        if (j == -1 || s[i] == p[j]) {
            ++i;
            ++j;
            if (j == pSize) {
                q = s + (i - pSize);
                break;
            }
        } else {
            j = r[j];
        }
    }
    free(r);
    return q;
}
