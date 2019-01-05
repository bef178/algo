#include <assert.h>
#include <stdlib.h>
#include <time.h>


/**
 * 随机函数扩域
 * randm() generates a random number in [0,m) in p=1/m
 * return a random number in [0,n) in p=1/n
 */
int Random_rand(const int n, int (*randm)(), int m) {
    assert(n > 0);
    assert(randm != NULL);
    assert(m > 1);

    int numBits = 1;
    int p = m;
    for (int i = n; (i = (i / m)) != 0; ) {
        numBits++;
        p *= m;
    }
    assert(p > n);

    int upperBound = n - p % n;
    while (true) {
        int k = randm();
        for (int i = 0; i < numBits; i++) {
            k = k * m + randm(); // extend as if m-based digit
        }
        if (k < upperBound) {
            return k % n;
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
 * 给定多个点，随机返回其中m个点，使每个点被选中的概率均等
 */
int Random_getReservoirSamples(int (*next)(), const int m, int * samples) {
    assert(next != NULL);
    assert(m > 0);
    assert(samples != NULL);
    srand(time(NULL));
    int i = 0;
    int v = EOF;
    while ((v = next()) != EOF) {
        if (i < m) {
            samples[i] = v;
        } else {
            int j = rand() % i;
            if (j < m) {
                // replace
                samples[j] = v;
            }
        }
        i++;
    }
    return i;
}
