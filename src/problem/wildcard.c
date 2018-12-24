#include <stdio.h>
#include <assert.h>

/**
 * wildcard: '*': any number of byte
 * wildcard: '?': 1 byte
 * s: string to test
 * p: wildcard pattern
 */
boolean wildcardMatches(const byte * s, const byte * p) {
    assert(s != NULL);
    assert(p != NULL);

    const byte * s1 = null; // substring to match from p1
    const byte * p1 = null; // next of asterisk if any

    while (*s != NUL) {
        if (*p == '*') {
            p1 = ++p;
            if (*p == NUL) {
                return true;
            }
            s1 = s;
            continue;
        }
        if (*p == '?' || *p == *s) {
            ++p;
            ++s;
            continue;
        }
        if (p1 != NULL) {
            if (*p == NUL || *p != *s) {
                p = p1;
                s = ++s1;
                continue;
            }
        }
        return false;
    }
    while (*p != NUL) {
        if (*p != '*') {
            return false;
        }
    }
    return true;
}

void testWildcard() {
    printf("testing wildcard ...\n");
    byte *p[][3] = {
        {"aa", "a", ""},
        {"aa", "aa", "\1"},
        {"aaa", "aa", ""},
        {"aa", "*", "\1"},
        {"aa", "a*", "\1"},
        {"ab", "?*", "\1"},
        {"aab", "c*a*b", ""},
        {"*ba", "*a", "\1"},
        {"abbb", "a*b*b", "\1"},
        {"abbb", "a*b*b?", "\1"},
    };
    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++) {
        int r = wildcardMatches(p[i][0], p[i][1]);
        assert(r == p[i][2][0]);
    }
}
