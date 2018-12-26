/**
 * longest palindrome substring
 * 最长回文
 */

#include <assert.h>

static int min(int i, int j) {
    return i <= j ? i : j;
}

byte * Palindrome_manacher(byte * a, int l, int r) {
    assert(a != NULL);
    assert(l >= 0 && r >= l);

    int n = r - l;

    // make [^#.#...#.#$]
    int n1 = 2 * n + 3;
    byte * s1 = calloc(n1, sizeof(byte));
    s1[0] = '^';
    for (int i = 0; i < n; i++) {
        s1[2 * i + 1] = '#';
        s1[2 * i + 2] = a[l + i];
    }
    s1[2 * n + 1] = '#';
    s1[2 * n + 2] = '$';

    // radius at i, including it self: p1[i] > 0 where i > 0
    int * p1 = calloc(n1, sizeof(int));

    int j1 = 0; // central point on p1

    int id = 0; // central point of the palindrome
    int mx = 0; // the r-boundary of @id

    for (int i = 1; i < n1 - 1; i++) {
        if (i < mx) {
            p1[i] = min(mx - i, p1[id - (i - id)]); // id - (i - id) is the mirror point of @i against @id
        } else {
            p1[i] = 1;
        }
        while (s1[i + p1[i]] == s1[i - p1[i]]) {
            p1[i]++;
        }
        if (i + p1[i] > mx) {
            id = i;
            mx = i + p1[i];
        }
        if (p1[j1] < p1[i]) {
            j1 = i;
        }
    }

    int length = p1[j1] - 1; // diameter in a
    int offset = l + (j1 - length - 1) / 2; // map back in a

    free(p1);
    p1 = NULL;

    free(s1);
    s1 = NULL;

    // copy palindrome
    byte * p = malloc(length + 1);
    memcpy(p, a + offset, length);
    p[length] = NUL;
    return p;
}

byte * Palindrome_find(byte * a, int l, int r) {
    assert(a != NULL);
    assert(l >= 0 && r >= l);

    int length = 0;
    int offset = l;

    // i as the 'central' point
    for (int i = l; i < r; i++) {
        int j = i;
        while (j < r && a[i] == a[j]) {
            j++;
        }
        j--;

        int l1 = i - 1;
        int r1 = j + 1;
        while (l1 >= l && r1 < r && a[l1] == a[r1]) {
            l1--;
            r1++;
        }
        l1++;
        r1--;
        if (length < r1 - l1 + 1) {
            length = r1 - l1 + 1;
            offset = l1;
        }
        i = j;
    }

    // copy palindrome
    byte * p = malloc(length + 1);
    memcpy(p, a + offset, length);
    p[length] = NUL;
    return p;
}

void testPadindrome() {
    byte * test1 = "ccccbaabbaabcac";
    byte * test2 = "ab";
    byte * sub = Palindrome_manacher(test1);
    printf("%s\n", sub);
}
