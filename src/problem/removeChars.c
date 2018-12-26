#include <stdio.h>
#include <string.h>

/**
 * remove any ch in chars from string
 * return the new length of string
 */
int removeChars(char * s, char * chars) {
    boolean toRemove[128] = { false };
    int n = strlen(chars);
    for (int i = 0; i < n; i++) {
        toRemove[chars[i]] = true;
    }

    char * p = s;
    char * q = NULL;
    while (*p != NUL) {
        if (toRemove[*p]) {
            if (q == NULL) {
                q = p;
            }
        } else {
            if (q != NULL) {
                *(q++) = *p;
            }
        }
        p++;
    }
    *q = NUL;
    return q - s;
}

void testRemoveChars() {
    char s[] = "the quick brown fox jumps over the lazy dog";
    int i = removeChars(s, "aeiouy");
    printf("%s| len %d\n", s, i);
}
