/**
 * 身份证号校验
 *
 * index    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17
 * p        1  1  0  1  0  8  1  9  4  9  1  0  0  1  0  0  1  4
 * p[17] is checksum
 * i = 0..16
 * k = (p[i] * pow(2, 17-i)) % 11
 */

int getIdChecksum(const char * p) {
    int k = 0;
    for (int i = 0; i < 17; i++) {
        k += (p[i] - '0') * (1 << (17 - i));
        k %= 11;
    }
    char c[11] = { '1', '0', 'x', '9', '8', '7', '6', '5', '4', '3', '2' };
    return c[k];
}

#include <assert.h>
#include <stdio.h>

void testGetIdChecksum() {
    char * p = "110108194910010014"; // 北京海淀
    assert(p[17] == getIdChecksum(p));
    printf("%s %c\n", p, getIdChecksum(p));
}
