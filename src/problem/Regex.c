/**
 * regex: '.' 1 byte
 * regex: '*' 0 or more prev byte
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static boolean matchesRegex(const byte * s, const byte * regex) {
    assert(s != NULL);
    assert(regex != NULL);

    if (regex[0] == NUL) {
        return s[0] == NUL;
    }

    assert(regex[0] != '*');

    // non-greedy '*'

    if (regex[0] == '.' && regex[1] == '*') {
        while (true) {
            if (matchesRegex(s, regex + 2)) {
                return true;
            }
            if (s[0] == NUL) {
                break;
            }
            s++;
        }
        return false;
    }

    if (regex[0] == s[0] && regex[1] == '*') {
        while (true) {
            if (matchesRegex(s, regex + 2)) {
                return true;
            }
            if (regex[0] != s[0]) { // including s[0] == NUL
                break;
            }
            s++;
        }
        return false;
    }

    if (regex[0] != s[0] && regex[1] == '*') {
        return matchesRegex(s, regex + 2);
    }

    // assert regex[1] != '*';

    if (regex[0] == '.') {
        if (s[0] != NUL) {
            return matchesRegex(s + 1, regex + 1);
        }
        return false;
    }

    if (regex[0] == s[0]) {
        // s[0] cannot be NUL since regex[0] is not NUL
        return matchesRegex(s + 1, regex + 1);
    }

    return false;
}

static boolean matchesRegex_dp(const byte * s, const byte * regex) {
    assert(s != NULL);
    assert(regex != NULL);

    int n = strlen(regex);

    // a valid regex will not start with '*' and have no neighboring '*'
    assert(regex[0] != '*');
    for (int i = 1; i < n; i++) {
        if (regex[i] == '*') {
            assert(regex[i - 1] != '*');
        }
    }

    // imagine @regex in a horizontal line, while @s in vertical
    // for regex[0..n) and s[0..m), the matrix should be m[m + 1][n + 1], extra "1" for empty string
    // that is, for string s[0..j] and regex[0..i], the matching result saves to m[j + 1][i + 1]
    // and, updating a row in matrix only requires the above row, so keeping tow rows to save memory

    boolean * p = calloc(n + 1, sizeof(boolean));

    // init current matching row
    p[0] = true; // empty string matches empty string
    for (int i = 0; i < n; i++) {
        if (regex[i] == '*') {
            p[i + 1] = p[i - 2 + 1];
        } else {
            p[i + 1] = false;
        }
    }

    boolean * q = calloc(n + 1, sizeof(boolean));
    for (int j = 0; s[j] != NUL; j++) {
        // swap
        boolean * t = q;
        q = p;
        p = t;
        p[0] = false; // non-empty s does not match empty regex
        for (int i = 0; i < n; i++) {
            if (regex[i] == '*') {
                if (regex[i - 1] == '.' || regex[i - 1] == s[j]) {
                    p[i + 1] = q[i + 1] // a* as many a
                        || p[i - 1 + 1] // a* as single a
                        || p[i - 2 + 1]; // a* as empty
                } else {
                    // a* as empty
                    p[i + 1] = p[i - 2 + 1];
                }
            } else if (regex[i] == '.') {
                p[i + 1] = q[i - 1 + 1];
            } else {
                if (regex[i] == s[j]) {
                    p[i + 1] = q[i - 1 + 1];
                } else {
                    p[i + 1] = false;
                }
            }
        }
    }

    boolean matches = p[n];
    free(p);
    free(q);

    return matches;
}

boolean Regex_matches(const byte * regex, const byte * s) {
    return matchesRegex_dp(s, regex);
}
