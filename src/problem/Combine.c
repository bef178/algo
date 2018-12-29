/**
 * Combination formula: C_n^m=\frac{n!}{m!(n-m)!}
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

int Combine_calculate(int n, int m) {
    assert(m >= 0 && n >= m);
    m = m < (n - m) ? m : (n - m);
    int p = 1;
    int q = 1;
    while (m > 0) {
        p *= n--;
        q *= m--;
    }
    return p / q;
}

static int getNumOfBitOne(int x) {
    int n = 0;
    while (x != 0) {
        x &= (x - 1);
        n++;
    }
    return n;
}

int Combine_nextIndex(int index) {
    assert (index > 0);
    int n = getNumOfBitOne(index);
    while (++index > 0) {
        if (getNumOfBitOne(index) == n) {
            return index;
        }
    }
    return -1;
}

int Combine_toBytes(byte * alphabet, int n, int index, byte * dst) {
    assert(n >= 0 && n < sizeof(int) * 8);
    assert(index >= 0);
    int j = 0;
    for (int i = 0; i < n; i++) {
        if ((index & (1 << (n - 1 - i))) != 0) {
            dst[j++] = alphabet[i];
        }
    }
    return j;
}

int Combine_toIndex(byte * alphabet, int n, byte * src, int m) {
    assert(n >= 0 && n < sizeof(int) * 8);
    int index = 0;
    for (int i = 0; i < m; i++) {
        byte * p = memchr(alphabet, src[i], n);
        if (p != NULL) {
            index |= 1 << (n - 1 - (p - alphabet));
        }
    }
    return index;
}

// C(5,2): "45" => 00011 => 00100 => 00101 => "35"
void Combine_printAll(byte * alphabet, int n, int m) {
    byte * dst = malloc(m + 1);
    dst[m] = NUL;
    int upperBound = (1 << n) - 1;
    int index = (1 << m) - 1;
    printf("%d %d %d %d\n", n, m, upperBound, index);
    while (index <= upperBound) {
        Combine_toBytes(alphabet, n, index, dst);
        printf("%s 0x%x\n", dst, index);
        index = Combine_nextIndex(index);
    }
    free(dst);
}

static int printAll2(int n, int m, byte * alphabet, int i, byte * dst, int j) {
    int count = 0;
    while (i < n) {
        dst[j] = alphabet[i];
        if (j == m - 1) {
            printf("%s\n", dst);
            count++;
        } else {
            count += printAll2(n, m, alphabet, i + 1, dst, j + 1);
        }
        i++;
    }
    return count;
}

void Combine_printAll2(byte * alphabet, int n, int m) {
    byte * dst = malloc(m + 1);
    dst[m] = NUL;
    int count = printAll2(n, m, alphabet, 0, dst, 0);
    free(dst);
}

void testCombine() {
    printf("testing combine ...\n");
    byte * alphabet = "abcde";
    Combine_printAll2(alphabet, strlen(alphabet), 2);
}
