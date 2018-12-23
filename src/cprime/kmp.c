/**
 * KMP algorithm
 *
 * since 2008-01-30
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// i |  0  1  2  3  4  5  6  7  8  |  0  1  2  3  4 |
// p |  a  b  a  a  b  c  a  b  a  |  a  a  a  b  c |
// r | -1  0 -1  1  0  2 -1  0 -1  | -1 -1 -1  2  0 |

static int * str_kmpRevise(const byte * p, const int n) {
    assert(p != NULL && *p != NUL);

    int * r = mem_pick(sizeof(int) * n);
    if (r == NULL) {
        perror("E: MEMORY ALLOCATION");
        exit(1);
    }

    int k = -1;
    r[0] = -1;
    for (int i = 1; i < n; i++) {
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

const byte * str_kmp(const byte * s, const byte * p) {
    assert(s != NULL && p != NULL);

    if (*p == NUL) {
        return s;
    } else if (*s == NUL) {
        return NULL;
    }

    size_t n = str_length(p);
    int * r = str_kmpRevise(p, n);

    int i = 0;
    int j = 0;
    while (s[i] != NUL) {
        if (j == -1 || s[i] == p[j]) {
            ++i;
            ++j;
            if (p[j] == NUL) {
                mem_drop(r);
                return s + i - n;
            }
        } else {
            j = r[j];
        }
    }
    mem_drop(r);
    return NULL;
}
