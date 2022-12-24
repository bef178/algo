/**
 * find longest palindrome substring
 * 最长回文
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void Manacher_findLongestPalindrome(int * a, int l, int r, int * outStartIndex, int * outEndIndex) {
    assert(a != NULL);
    assert(l >= 0);
    assert(r >= l); // allow empty string

    int n = r - l;

    // make [^#.#...#.#$]
    int n1 = 2 * n + 3;
    int * s1 = calloc(n1, sizeof(int));
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
            p1[i] = Int32_min(mx - i, p1[id - (i - id)]); // id - (i - id) is the mirror point of @i against @id
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

    int resultLength = p1[j1] - 1; // diameter in a
    int resultOffset = l + (j1 - resultLength - 1) / 2; // map back in a

    free(p1);
    p1 = NULL;

    free(s1);
    s1 = NULL;

    *outStartIndex = resultOffset;
    *outEndIndex = resultOffset + resultLength;
}

void findLongestPalindrome(int * a, int l, int r, int * outStartIndex, int * outEndIndex) {
    assert(a != NULL);
    assert(l >= 0);
    assert(r >= l); // allow empty string

    int resultLength = 0;
    int resultOffset = l;

    // i as the 'central-left' point
    for (int i = l; i < r; i++) {
        int j = i + 1;
        while (j < r && a[i] == a[j]) {
            j++;
        }
        j--;

        int i1 = i - 1;
        int j1 = j + 1;
        while (i1 >= l && j1 < r && a[i1] == a[j1]) {
            i1--;
            j1++;
        }
        i1++;
        j1--;
        if (resultLength < j1 - i1 + 1) {
            resultLength = j1 - i1 + 1;
            resultOffset = i1;
        }
        i = j;
    }

    *outStartIndex = resultOffset;
    *outEndIndex = resultOffset + resultLength;
}

static
void print(char * a, int l, int r, int start, int end) {
    for (int i = l; i < r; i++) {
        putchar(a[i]);
    }
    putchar('\n');
    for (int i = l; i < r; i++) {
        if (i >= start && i < end) {
            putchar('^');
        } else {
            putchar(' ');
        }
    }
    putchar('\n');
}

static
void printLongestPalindrome(char * s) {
    int start = -1;
    int end = -1;
    int n = strlen(s);
    int a[n];
    for (int i = 0; i < n; i++) {
        a[i] = s[i];
    }
    Manacher_findLongestPalindrome(a, 0, n, &start, &end);
    print(s, 0, n, start, end);
}

int main() {
    printLongestPalindrome("ccccbaabbaabcac");
    printLongestPalindrome("ab");
    printLongestPalindrome("a");
    printLongestPalindrome("");
}
