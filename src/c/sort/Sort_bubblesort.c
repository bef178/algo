#include <assert.h>

/**
 * stable, in-place, average/worst O(n^2)
 */
void Sort_bubblesort(int * a, int l, int r) {
    assert(a != null);
    assert(l >= 0);
    assert(r >= l);
    int next = l;
    boolean goesNext = true;
    while (goesNext) {
        goesNext = false;
        for (int i = r - 2; i >= next; i--) {
            if (a[i] > a[i + 1]) {
                Int32Array_swap(a, i, i + 1);
                goesNext = true;
            }
        }
        next++;
    }
}
