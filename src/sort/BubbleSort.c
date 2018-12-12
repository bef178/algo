void BubbleSort_sort(int * a, int l, int r) {
    boolean swapped = true;
    while (swapped) {
        swapped = false;
        for (int i = r - 1; i > l; i--) {
            if (a[i] < a[i - 1]) {
                swap(a, i, i - 1);
                swapped = true;
            }
        }
        r--;
    }
}
