/**
 * shell sort, a.k.a diminishing increment sort, with inner insertion sort
 * unstable, in-place, average ~O(n^1.5), worst O(n^2)
 */
void Sort_shellsort(int * a, int l, int r) {
    static const int gaps[] = { 701, 301, 132, 57, 23, 10, 4, 1 }; // Ciura, 2001
    int n = sizeof(gaps) / sizeof(int);
    for (int i = 0; i < n; i++) {
        int gap = gaps[i];
        Sort_insertionsort_step(a, l, r, gap);
    }
}
