/**
 * 蓄水池抽样 Reservoir Sampling
 * 给定多个点，随机拾取其中n个点，使每个点被选中的概率均等
 *
 * leetcode #382 medium
 * https://leetcode.com/problems/linked-list-random-node/
 */

#include <assert.h>
#include <stdlib.h>
#include <time.h>

// return the number of samples
int reservoirSamples(int (*next)(), int * samples, const int n) {
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
