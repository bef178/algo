/**
 * by selecting the top of rest
 *
 * average O(n^2), generally performs worse than the similar insertion sort
 * unstable
 * in-place
 */

void ssort(int * a, int l, int r) {
    for (int i = l; i < r; i++) {
        int k = i;
        for (int j = i; j < r; j++) {
            if (a[j] < a[k]) {
                k = j;
            }
        }
        if (i != k) {
            swap(a, i, k);
        }
    }
}
