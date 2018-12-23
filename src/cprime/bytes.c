#include <assert.h>
#include <stdlib.h>

void * mem_pick(int n) {
    assert(n >= 0);
    void * p = calloc(1, n);
    assert(p != NULL);
    return p;
}

void mem_drop(void * p) {
    if (p != NULL) {
        free(p);
    }
}

void mem_reset(void * p, int n) {
    assert(p != NULL);
    assert(n > 0);
    byte * q = (byte *)p;
    while (n--) {
        *q++ = 0;
    }
}

boolean mem_resize(void ** p, int n) {
    assert(n > 0);
    void * q = realloc(*p, n);
    if (q != NULL) {
        *p = q;
        return true;
    }
    return false;
}

int mem_compare(const byte * p1, const byte * p2, int n) {
    assert(p1 != NULL);
    assert(p2 != NULL);
    assert(n >= 0);

    const word * w1 = (const word *) p1;
    const word * w2 = (const word *) p2;
    while (n >= sizeof(word)) {
        if (*w1 != *w2) {
            return *w1 < *w2 ? -1 : 1;
        }
        ++w1;
        ++w2;
        n -= sizeof(word);
    }

    p1 = (const byte *) w1;
    p2 = (const byte *) w2;
    while (n > 0 && *p1 == *p2) {
        ++p1;
        ++p2;
        --n;
    }
    return n == 0 ? 0 : (*p1 < *p2 ? -1 : 1);
}

void mem_copy(byte * dst, const byte * src, int n) {
    assert(dst != NULL);
    assert(src != NULL);
    assert(n >= 0);
    // XXX fail in case of overlapping

    const word * src1 = (const word *) src;
    word * dst1 = (word *) dst;
    while (n >= sizeof(word)) {
        *dst1++ = *src1++;
        n -= sizeof(word);
    }

    src = (const byte *) src1;
    dst = (byte *) dst1;
    while (n-- > 0) {
        *dst++ = *src++;
    }
}
