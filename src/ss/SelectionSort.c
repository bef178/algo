/**
 * by selecting the top of rest
 *
 * average O(n^2), generally performs worse than the similar insertion sort
 * unstable
 * in-place
 */

void SelectionSort_sort(int * a, int l, int r) {
    for (int i = l; i < r; i++) {
        int k = i;
        for (int j = i; j < r; j++) {
            if (a[j] < a[k]) {
                k = j;
            }
        }
        if (i != k) {
            Int32Array_swap(a, i, k);
        }
    }
}
