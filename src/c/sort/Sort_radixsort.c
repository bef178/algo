#include <memory.h>

/**
 * non-comparion sort, by putting elements into buckets then collecting
 * two kinds:
 *  lsd: [2,1,10] => [1,2,10] // least significant digit
 *  msd: [2,1,10] => [1,10,2] // lexicographic order
 */
void Sort_radixsort(int * a, int l, int r) {
    const int RADIX = 10;
    int maxKey = a[Int32Array_indexOfMax(a, l, r)];

    int c[RADIX];
    int a1[r - l];

    // for each radix
    for (int exp = 1; exp < maxKey; exp *= RADIX) {
        // inner counting sort
        memset(c, 0, sizeof(c));
        for (int i = l; i < r; i++) {
            c[(a[i] / exp) % RADIX]++;
        }
        for (int i = l + 1; i < RADIX; i++) {
            c[i] += c[i - 1];
        }
        for (int i = r - 1; i >= l; i--) {
            a1[--c[(a[i] / exp) % RADIX]] = a[i];
        }

        // collect
        for (int i = 0; i < r - l; i++) {
            a[i + l] = a1[i];
        }
    }
}
