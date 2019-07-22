/**
 * by inserting into an already sorted list
 */

/**
 * straight insertion sort
 * average O(n^2)
 * stable
 * in-place
 */
void InsertionSort_sort(int * a, int l, int r) {
    for (int i = l + 1; i < r; i++) {
        int t = a[i];
        int j = i - 1;
        while (j >= l && a[j] > t) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = t;
    }
}

// insertion sort with binary search
static void InsertionSort_sort1(int * a, int l, int r) {
    for (int i = l + 1; i < r; i++) {
        int t = a[i];
        int k = BinarySearch_upperBound(a, 0, i, a[i]);
        if (k != i) {
            int j = i - 1;
            while (j >= k) {
                a[j + 1] = a[j];
                j--;
            }
            a[k] = t;
        }
    }
}
