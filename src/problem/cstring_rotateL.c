/**
 * 字符串旋转.c
 */

static int gcd(int m, int n) {
    while (m != n) {
        if (m > n) {
            m -= n;
        } else {
            n -= m;
        }
    }
    return m;
}

void str_rotateL(byte * a, int l, int r, int m) {
    int n = r - l;
    int g = gcd(m, n);
    if (g == n) {
        return;
    }
    for (int i = 0; i < g; i++) {
        int t = a[l + i];
        int j = i;
        while (true) {
            int k = (j + m) % n;
            if (k == i) {
                break;
            }
            a[l + j] = a[l + k];
            j = k;
        }
        a[l + j] = t;
    }
}

#include <assert.h>
#include <stdio.h>
#include <string.h>

void testCstringRotateL() {
    printf("testing CstringRotateL ...\n");
    byte a[] = "0123456789";
    str_rotateL(a, 5, 8, 2);
    assert(memcmp("0123475689", a, sizeof(a) / sizeof(byte)) == 0);
}
