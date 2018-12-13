static int findMedian(int * a, int i, int j, int k) {
    int max;
    int min;
    if (a[i] < a[j]) {
        min = i;
        max = j;
    } else {
        min = j;
        max = i;
    }
    if (a[min] > a[k]) {
        min = k;
    }
    if (a[max] < a[k]) {
        max = k;
    }
    return i + j + k - min - max;
}

// every swap occurs in partition()
// divide & conquer
static int partition(int * a, int l, int r) {
    // assert l < r;
    r--;
    int p = findMedian(a, l, r, l + (r - l) / 2);
    if (p != l) {
        swap(a, p, l);
    }
    p = l;
    while (l < r) {
        while (l < r && a[r] > a[p]) {
            r--;
        }
        while (l < r && a[l] <= a[p]) {
            l++;
        }
        if (l < r) {
            swap(a, l, r);
        }
    }
    if (p != r) {
        swap(a, p, r);
    }
    return r;
}

void QuickSort_sort(int * a, int l, int r) {
    if (l >= r - 1) {
        return;
    }
    int i = partition(a, l, r);
    QuickSort_sort(a, l, i);
    QuickSort_sort(a, i + 1, r);
}
