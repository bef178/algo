/**
 * regex: '.' 1 byte
 * regex: '*' 0 or more prev byte
 */

#include <assert.h>

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

boolean Regex_matches(const byte * regex, const byte * s) {
    return matchesRegex(s, regex);
}
