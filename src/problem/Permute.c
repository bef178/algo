#include <assert.h>
#include <stdlib.h>

static int factorial(int n) {
    int p = 1;
    while (n > 0) {
        p *= n--;
    }
    return p;
}

static void swapByte(byte * a, int i, int j) {
    a[i] ^= a[j];
    a[j] ^= a[i];
    a[i] ^= a[j];
}

int Permute_calculate(int n, int m) {
    assert(m >= 0 && n >= m);
    int p = 1;
    for (int i = n; i > n - m; i--) {
        p *= i;
    }
    return p;
}

/**
 * Problem: Next Permutation
 * re-arranges numbers lexicographically into next greater permutation of numbers
 */
void Permute_nextPermutation(byte * a, int n) {
    // starting from right, find the first a[k] < a[k + 1]
    int k = -1;
    for (int i = n - 2; i >= 0; i--) {
        if (a[i] < a[i + 1]) {
            k = i;
            break;
        }
    }

    if (k != -1) {
        for (int i = n - 1; i > k; i--) {
            if (a[i] > a[k]) {
                swapByte(a, i, k);
                break;
            }
        }
    }

    for (int i = k + 1, j = n - 1; i < j; i++, j--) {
        swapByte(a, i, j);
    }
}

static int getAvailable(byte * alphabet, int n, byte * used, int j) {
    for (int i = 0; i < n; i++) {
        if (used[i] == 1) {
            continue;
        }
        if (j == 0) {
            used[i] = 1;
            return alphabet[i];
        } else {
            j--;
        }
    }
}

/**
 * Given alphabet and index, find the permutation
 */
void Permute_fromIndex(byte * alphabet, int n, int index, byte * dst) {
    byte * used = calloc(n, sizeof(byte));
    for (int i = 0; i < n; i++) {
        int fi = factorial(n - 1 - i);
        int j = index / fi;
        dst[i] = getAvailable(alphabet, n, used, j);
        index -= j * fi;
    }
}

static int printAll2(int n, int m, byte * alphabet, byte * used, byte * dst, int j) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (used[i] == 1) {
            continue;
        }
        dst[j] = alphabet[i];
        used[i] = 1;
        if (j == m - 1) {
            count++;
            printf("%s\n", dst);
        } else {
            count += printAll2(n, m, alphabet, used, dst, j + 1);
        }
        dst[j] = NUL;
        used[i] = 0;
    }
    return count;
}

void Permute_printAll2(byte * alphabet, int n, int m) {
    byte * dst = malloc(m + 1);
    dst[m] = NUL;
    byte * used = calloc(n, sizeof(byte));
    int count = printAll2(n, m, alphabet, used, dst, 0);
    free(used);
    free(dst);
}

#include <string.h>

void testPermute() {
    printf("testing permute ...\n");

    byte p[] = "12345";

    Permute_fromIndex("12345", 5, 4, p);
    printf("12345 index 4: %s\n", p);

    Permute_fromIndex("12345", 5, 89, p);
    printf("12345 index 89: %s\n", p);

    printf("%s next: ", p);
    Permute_nextPermutation(p, strlen(p));
    printf("%s\n", p);

    Permute_fromIndex("12345", 5, 90, p);
    printf("12345 index 90: %s\n", p);

    byte * alphabet = "abcd";
    Permute_printAll2(alphabet, strlen(alphabet), 2);
}
