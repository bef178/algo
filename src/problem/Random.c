#include <assert.h>
#include <stdlib.h>
#include <time.h>


/**
 * 随机函数扩域
 * randm() generates a random number in [0,m) in p=1/m
 * return a random number in [0,n) in p=1/n
 */
int Random_randn(const int n, int (*randm)(), int m) {
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

/**
 * 概率平均化
 * rand2p provides 0 in p, 1 in (1-p)
 */
int Random_rand2(int (*rand2p)()) {
    assert(rand2p != NULL);
    int i = rand2p();
    int j = rand2p();
    while (true) {
        if (i + j == 1) {
            return i;
        }
    }
}

/**
 * 蓄水池采样 Reservoir Sampling
 * 给定多个点，随机拾取其中n个点，使每个点被选中的概率均等
 * return Reservoir size
 */
int Random_getReservoirSamples(int (*next)(), int * samples, const int n) {
    assert(next != NULL);
    assert(n > 0);
    assert(samples != NULL);
    srand(time(NULL));
    int i = 0;
    int v = EOF;
    while ((v = next()) != EOF) {
        if (i < n) {
            samples[i] = v;
        } else {
            int j = rand() % i;
            if (j < n) {
                // replace
                samples[j] = v;
            }
        }
        i++;
    }
    return i;
}
