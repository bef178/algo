#include <assert.h>
#include <stdlib.h>

#include <string.h>

void Permutation_getByIndex(byte *, int, int, byte *);
void Permutation_getNext(byte *, int);

void testPermutation() {
    printf("testing Permutation ...\n");

    byte p[] = "12345";

    Permutation_getByIndex("12345", 5, 4, p);
    assert(strncmp("12534", p, 5) == 0);

    Permutation_getByIndex("12345", 5, 89, p);
    assert(strncmp("43521", p, 5) == 0);

    Permutation_getNext(p, strlen(p));
    assert(strncmp("45123", p, 5) == 0);

    Permutation_getByIndex("12345", 5, 90, p);
    assert(strncmp("45123", p, 5) == 0);
}
