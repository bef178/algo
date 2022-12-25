#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define NUL ('\0')

/**
 * a valid regex will not start with '*' and have no neighboring '*'
 */
public
boolean Regex_isValid(const byte * regex) {
    if (regex == NULL) {
        return false;
    }

    boolean meetsAsterisk = true;
    const int n = strlen(regex);
    for (int i = 0; i < n; i++) {
        if (regex[i] == '*') {
            if (meetsAsterisk) {
                return false;
            }
            meetsAsterisk = true;
        } else {
            meetsAsterisk = false;
        }
    }
    return true;
}

static
boolean matches(const byte * regex, const byte * s) {
    assert(Regex_isValid(regex));
    assert(s != NULL);

    if (regex[0] == NUL) {
        return s[0] == NUL;
    }

    // non-greedy '*'

    if (regex[0] == '.' && regex[1] == '*') {
        while (true) {
            if (matches(regex + 2, s)) {
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
            if (matches(regex + 2, s)) {
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
        return matches(regex + 2, s);
    }

    // assert regex[1] != '*';

    if (regex[0] == '.') {
        if (s[0] != NUL) {
            return matches(regex + 1, s + 1);
        }
        return false;
    }

    if (regex[0] == s[0]) {
        // s[0] cannot be NUL since regex[0] is not NUL
        return matches(regex + 1, s + 1);
    }

    return false;
}

static
boolean matches_dp(const byte * regex, const byte * s) {
    assert(Regex_isValid(regex));
    assert(s != NULL);

    int n = strlen(regex);

    // imagine regex in horizontal while s in vertical
    // for regex[0..n) and s[0..m), the matrix should be a[m + 1][n + 1]; a[0][.] and a[.][0] for empty string
    // that is, for regex[0..i] and s[0..j], the matching result saves to a[j + 1][i + 1]
    // keep two rows to save memory

    // init current matching row
    boolean * p = calloc(n + 1, sizeof(boolean));
    p[0] = true; // empty string matches empty regex
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
        p[0] = false; // non-empty string does not match empty regex
        for (int i = 0; i < n; i++) {
            if (regex[i] == '*') {
                if (regex[i - 1] == '.' || regex[i - 1] == s[j]) {
                    p[i + 1] = q[i + 1] // a* as many a
                        || p[i - 1 + 1] // a* as single a
                        || p[i - 2 + 1]; // a* as empty
                } else {
                    p[i + 1] = p[i - 2 + 1]; // a* as empty
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

public
boolean Regex_matches(const byte * regex, const byte * s) {
    return matches_dp(regex, s);
}
