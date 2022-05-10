#include <assert.h>
#include <stdlib.h>
#include <time.h>

/**
 * 随机函数扩域
 * Given randm() generating a random number in [0,m) in p=1/m
 * return a random number in [0,n) in p=1/n
 */
int randn(const int n, int (*randm)(), int m) {
    assert(n > 0);
    assert(randm != NULL);
    assert(m > 1);

    int numBits = 1;
    int extendedBound = m;
    while (extendedBound < n) {
        numBits++;
        extendedBound *= m; // caution: overflow
    }
    int upperBound = extendedBound - extendedBound % n;

    while (true) {
        int r = 0;
        for (int i = 0; i < numBits; i++) {
            r = r * m + randm(); // extend as if m-based digit
        }
        if (r < upperBound) {
            return r % n;
        }
    }
}
