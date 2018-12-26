/**
 * basic regex
 *
 * supported special alphabet [ '.', '*' ]
 */

#include <assert.h>
#include <stdlib.h>

/**
 * return true iff regex matches entire @s
 */
boolean BasicRegex_matches(const byte * regex, const byte * s) {
    assert(regex != NULL);
    assert(s != NULL);

    if (regex[0] == NUL) {
        return s[0] == NUL;
    }

    assert(regex[0] != '*');

    // non-greedy for '*'

    if (regex[0] == '.' && regex[1] == '*') {
        while (true) {
            if (BasicRegex_matches(regex + 2, s)) {
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
            if (BasicRegex_matches(regex + 2, s)) {
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
        return BasicRegex_matches(regex + 2, s);
    }

    // assert regex[1] != '*';

    if (regex[0] == '.') {
        if (s[0] != NUL) {
            return BasicRegex_matches(regex + 1, s + 1);
        }
        return false;
    }

    if (regex[0] == s[0]) {
        // s[0] cannot be NUL if it gets here
        return BasicRegex_matches(regex + 1, s + 1);
    }

    return false;
}

void testRegex() {
    byte * testcases[][3] = {
        { "aa", "a", "\0" },
        { "aa", "aa", "\1" },
        { "aaa", "aa", "\0" },
        { "aa", "a*", "\1" },
        { "aa", ".*", "\1" },
        { "ab", ".*", "\1" },
        { "aab", "c*a*b", "\1" },
        { "a",  "ab*a", "\0" },
        { "aa", "aa*a", "\1" },
    };
    for (int i = 0; i < sizeof(testcases) / sizeof(testcases[0]); i++) {
        boolean result = BasicRegex_matches(testcases[i][1], testcases[i][0]);
        assert(result == testcases[i][2][0]);
    }
}
