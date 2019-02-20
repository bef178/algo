#include <string.h>

/**
 * RadixSort
 * by dropping into buckets and collecting
 * two kinds:
 *  lsd: [2,1,10] => [1,2,10]
 *  msd: [2,1,10] => [1,10,2] // using lexicographic order
 * non-comparion
 */
void RadixSort_leastSignificantDigit(int * a, int l, int r) {

    static const int RADIX = 10;

    int max = a[indexOfMax(a, l, r)];

    int c[RADIX];
    int t[r - l];
    for (int exp = 1; max > exp; exp *= RADIX) {
        // inner counting sort
        memset(c, 0, sizeof(c));
        for (int i = l; i < r; i++) {
            c[(a[i] / exp) % RADIX]++;
        }
        for (int i = l + 1; i < RADIX; i++) {
            c[i] += c[i - 1];
        }
        for (int i = r - 1; i >= l; i--) {
            t[--c[(a[i] / exp) % RADIX]] = a[i];
        }
        memcpy(a + l, t, (r - l) * sizeof(int));
    }
}
