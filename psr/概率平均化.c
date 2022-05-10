#include <assert.h>
#include <stdlib.h>
#include <time.h>

/**
 * 概率平均化
 * Given rand2p, providing 0 in p, 1 in (1-p)
 */
int rand2(int (*rand2p)()) {
    assert(rand2p != NULL);
    int i = rand2p();
    int j = rand2p();
    while (true) {
        if (i + j == 1) {
            return i;
        }
    }
}
