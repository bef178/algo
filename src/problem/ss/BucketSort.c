#include <string.h>

// the k most significant bits of x
static int msbits(int x, int k) {
    return ((unsigned) x) >> (sizeof(x) - k);
}

/**
 * bucket sort a.k.a. bin sort
 * for multiple keys by dropping into buckets with most-significant key and sort respectively
 * distribution sort
 */
void BucketSort_sort(int * a, int l, int r) {

    static const int k = 4;

    // var buckets;
    for (int i = l; i < r; i++) {
        // add a[i] into buckets[msbits(a[i], k)]
    }
    for (int i = 0; i < (1 << k); i++) {
        // sort buckets[i]
    }
    for (int i = 0; i < (1 << k); i++) {
        // add each item in buckets[i] back to a
    }
}
