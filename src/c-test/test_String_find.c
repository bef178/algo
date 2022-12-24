#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int BoyerMoore_find(byte * s, int sLen, byte * p, int pLen);
int Kmp_find(byte * s, int sLen, byte * p, int pLen);
int String_find(byte * s, int sLen, byte * p, int pLen);

static
void testOne(byte * s, int sLen, byte * p, int pLen, const int expected) {
    int actual;

    actual = BoyerMoore_find(s, sLen, p, pLen);
    if (actual != expected) {
        printf("algo: BoyerMoore, input: %s, %s, expected: %d, actual: %d\n", s, p, expected, actual);
        assert(false);
    }

    actual = Kmp_find(s, sLen, p, pLen);
    if (actual != expected) {
        printf("algo: Kmp, input: %s, %s, expected: %d, actual: %d\n", s, p, expected, actual);
        assert(false);
    }

    actual = String_find(s, sLen, p, pLen);
    if (actual != expected) {
        printf("algo: Naive, input: %s, %s, expected: %d, actual: %d\n", s, p, expected, actual);
        assert(false);
    }
}

void test_String_find() {
    printf("testing String_find ...\n");

    byte * s = "HERE IS A SIMPLE EXAMPLE";
    byte * p = "EXAMPLE";
    testOne(s, strlen(s), p, strlen(p), strstr(s, p) - (char *) s);

    s = "ABCDABEABDCBCDDBBCDBACD";
    p = "BCDBACD";
    testOne(s, strlen(s), p, strlen(p), strstr(s, p) - (char *) s);

    s = "hello";
    p = "ll";
    testOne(s, strlen(s), p, strlen(p), strstr(s, p) - (char *) s);

    s = "aaaaa";
    p = "bba";
    testOne(s, strlen(s), p, strlen(p), -1);

    s = "a";
    p = "a";
    testOne(s, strlen(s), p, strlen(p), strstr(s, p) - (char *) s);

    s = "aaa";
    p = "aaaa";
    testOne(s, strlen(s), p, strlen(p), -1);

    s = "mississippi";
    p = "a";
    testOne(s, strlen(s), p, strlen(p), -1);

    s = "mississippi";
    p = "issi";
    testOne(s, strlen(s), p, strlen(p), strstr(s, p) - (char *) s);
}
