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

void Cstring_rotateL(byte * a, int l, int r, int m) {
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

#include <stdio.h>

void testRotateL() {
    byte a[] = "0123456789";
    Cstring_rotateL(a, 5, 8, 2);
    printf("%s\n", a);
}
