#include <assert.h>
#include <stdlib.h>

public
int String_find(const byte * s, const int sLen, const byte * p, const int pLen) {
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

    for (int i = 0; i < sLen; i++) {
        int si = i;
        int pi = 0;
        while (si < sLen && pi < pLen && s[si] == p[pi]) {
            si++;
            pi++;
        }
        if (pi == pLen) {
            return i;
        }
        if (si == sLen) {
            break;
        }
    }
    return -1;
}
