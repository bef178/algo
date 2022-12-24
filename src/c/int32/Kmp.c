/**
 * KMP (Knuth Morris Pratt) pattern searching
 *
 * implementation since 2008-01-30
 */

// i |  0  1  2  3  4  5  6  7  8  |  0  1  2  3  4 |
// p |  a  b  a  a  b  c  a  b  a  |  a  a  a  b  c |
// r | -1  0 -1  1  0  2 -1  0 -1  | -1 -1 -1  2  0 |

#include <assert.h>

static
void Kmp_calcReviseTable(const byte * p, const int pLen, int * reviseTable) {
    assert(p != NULL && pLen > 0);
    assert(reviseTable != NULL);

    for (int i = 0; i < pLen; i++) {
        reviseTable[i] = 0;
    }

    int k = -1;
    reviseTable[0] = -1;
    for (int i = 1; i < pLen; i++) {
        if (k != -1 && p[i - 1] != p[k]) {
            k = reviseTable[k];
        }
        ++k;
        if (p[i] == p[k]) {
            reviseTable[i] = reviseTable[k];
        } else {
            reviseTable[i] = k;
        }
    }
}

public
int Kmp_find(byte * s, int sLen, byte * p, int pLen) {
    assert(s != NULL && sLen >= 0);
    assert(p != NULL && pLen >= 0);

    if (pLen == 0) {
        return 0;
    }
    if (sLen == 0) {
        return -1;
    }
    if (pLen > sLen) {
        return -1;
    }

    int reviseTable[pLen];
    Kmp_calcReviseTable(p, pLen, reviseTable);

    byte * q = NULL;

    int i = 0;
    int j = 0;
    while (i < sLen) {
        if (j == -1 || s[i] == p[j]) {
            ++i;
            ++j;
            if (j == pLen) {
                q = s + (i - pLen);
                break;
            }
        } else {
            j = reviseTable[j];
        }
    }
    return q == NULL ? -1 : q - s;
}
