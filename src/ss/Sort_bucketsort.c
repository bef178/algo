#include <memory.h>

// the k most significant bits of x
static
int msbits(int x, int k) {
    return ((unsigned) x) >> (sizeof(x) - k);
}

/**
 * for multiple keys by putting elements into buckets according to most-significant key then sort respectively
 * distribution sort
 */
void Sort_bucketsort(int * a, int l, int r) {
    const int k = 4;

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
