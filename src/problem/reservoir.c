/**
 * 蓄水池采样 Reservoir Sampling
 *
 * 给定n个点，随机返回其中m个点，使每个点被选中的概率均等
 */

#include <stdlib.h>
#include <time.h>

int * getReservoirSamples(int * a, int n, int m) {
    srand(time(NULL));
    int * samples = calloc(m, sizeof(int));
    for (int i = 0; i < m; i++) {
        samples[i] = a[i];
    }
    for (int i = m; i < n; i++) {
        int j = rand() % i;
        if (j < m) {
            samples[j] = a[i];
        }
    }
    return samples;
}
