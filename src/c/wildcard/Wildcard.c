/**
 * wildcard: '?': matches any single character
 * wildcard: '*': matches any sequence of characters, including empty sequence
 */

#include <assert.h>

#define NUL ('\0')

public
boolean Wildcard_matches(const byte * wildcard, const byte * s) {
    assert(wildcard != NULL);
    assert(s != NULL);

    const byte * p1 = NULL; // next of an '*', save for backtrace
    const byte * s1 = NULL; // first 0 or more bytes of s1 will be consumed by above '*'

    while (*s != NUL) {
        if (*wildcard == '*') {
            p1 = ++wildcard;
            if (*wildcard == NUL) {
                return true;
            }
            s1 = s; // not move forward in case '*' consuming 0 unit
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
