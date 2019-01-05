/**
 * wildcard: '*': 0 or more bytes
 * wildcard: '?': 1 byte
 */

#include <assert.h>

static boolean matchesWildcard(const byte * s, const byte * wildcard) {
    assert(s != NULL);
    assert(wildcard != NULL);

    const byte * p1 = NULL; // next of an '*', save for backtrace
    const byte * s1 = NULL; // first 0 or more bytes of s1 will be consumed by above '*'

    while (*s != NUL) {
        if (*wildcard == '*') {
            p1 = ++wildcard;
            if (*wildcard == NUL) {
                return true;
            }
            s1 = s;
            continue;
        }
        if (*wildcard == '?' || *wildcard == *s) {
            wildcard++;
            s++;
            continue;
        }
        if (p1 != NULL) {
            if (*wildcard == NUL || *wildcard != *s) {
                wildcard = p1;
                s = ++s1;
                continue;
            }
        }
        return false;
    }
    while (*wildcard != NUL) {
        if (*wildcard != '*') {
            return false;
        }
        wildcard++;
    }
    return true;
}

boolean Wildcard_matches(const byte * wildcard, const byte * s) {
    return matchesWildcard(s, wildcard);
}
