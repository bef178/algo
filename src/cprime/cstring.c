/**
 * minimal complete subset of string operations:
 * concatenate, compare, copy, length, substring
 */

#include <assert.h>
#include <stdlib.h>

int str_concatenate(byte * dst, const byte * src, const int n) {
    assert(dst != NULL);
    assert(src != NULL);
    assert(n >= 0);

    dst += str_length(dst);
    int i = 0;
    while (i++ < n && (*dst++ = *src++) != NUL) {
        // dummy
    }
    return i;
}

int str_compare(const byte * s1, const byte * s2, const int n) {
    assert(n >= 0);

    if (s1 == s2) {
        return 0;
    }

    if (s1 == NULL) {
        return -1;
    } else if (s2 == NULL) {
        return 1;
    }

    int i = 0;
    while (i++ < n && *s1 != NUL && *s1++ == *s2++) {
        // dummy
    }
    return *s1 - *s2;
}

int str_copy(byte * dst, const byte * src, const int n) {
    assert(dst != NULL);
    assert(src != NULL);
    assert(n >= 0);
    int i = 0;
    while (i++ < n && (*dst++ = *src++) != NUL) {
        // dummy
    }
    return i;
}

int str_indexOf(const byte * s, const byte * p) {
    if (s == NULL || p == NULL) {
        return -1;
    }
    int i = 0;
    while (s[i] != NUL) {
        const byte * s1 = s + i;
        const byte * p1 = p;
        while (*p1 != NUL && *s1 == *p1) {
            s1++;
            p1++;
        }
        if (*p1 == NUL) {
            return i;
        }
        if (*s1 == NUL) {
            break;
        }
        i++;
    }
    return -1;
}

int str_length(const byte * s) {
    assert(s != NULL);
    const byte * p = s;
    while (*s != NUL) {
        ++s;
    }
    return (int)(s - p);
}

int str_substring(byte * dst, const byte * src, int i, int j) {
    assert(src != NULL);
    assert(dst != NULL);

    int n = str_length(src);
    if (i < 0) {
        i += n;
    }
    if (j < 0) {
        j += n;
    }
    assert(i >= 0 && i < n);
    assert(j >= i && j < n);

    src += i;
    j -= i;
    int size = 0;
    while (j-- && *src != NUL) {
        *dst++ = *src++;
        ++size;
    }
    *dst = NUL;
    return size;
}

byte * str_trimFore(byte * s) {
    assert(s != NULL);
    while (isWhitespace(*s)) {
        ++s;
    }
    return s;
}

byte * str_trimHind(byte * s) {
    assert(s != NULL);
    byte * p = s;
    while (*p != NUL) {
        ++p;
    }
    while (--p >= s && isWhitespace(*p)) {
        // dummy
    }
    return ++p;
}
