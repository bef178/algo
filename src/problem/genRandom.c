/**
 * 随机函数扩域
 */

#include <assert.h>

int rand7() {
    // fake as already provided
}

int rand49() {
    return rand7() * 7 + rand7(); // extend as if 7-based digit
}

// return [0,n) via rand49()
int rand(int n) {
    assert(n >= 0 && n < 49);
    int upperBound = n - 49 % n;
    while (true) {
        int k = rand49();
        if (k < upperBound) {
            return k % n;
        }
    }
}

/**
 * 概率平均化
 */

// return 0 in p, 1 in (1-p)
int rand2p() {
    // fake as already provided
}

int rand2() {
    int i = rand2p();
    int j = rand2p();
    while (true) {
        if (i + j == 1) {
            return i;
        }
    }
}
