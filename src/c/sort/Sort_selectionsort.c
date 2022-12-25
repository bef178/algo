/**
 * by selecting the top of rest
 * unstable, in-place, average O(n^2)
 * generally performs worse than the similar insertion sort
 */
void Sort_selectionsort(int * a, int l, int r) {
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
