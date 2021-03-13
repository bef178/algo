static
int Sort_quicksort_findPivotIndex(int* a, int i, int j) {
    int k = i + (j - i) / 2;
    if (a[i] <= a[j]) {
        if (a[k] >= a[j]) {
            return j;
        } else if (a[k] >= a[i]) {
            return k;
        } else {
            return i;
        }
    } else {
        if (a[k] >= a[i]) {
            return i;
        } else if (a[k] >= a[j]) {
            return k;
        } else {
            return j;
        }
    }
}

// divide & conquer
static
int Sort_quicksort_partition(int* a, int l, int r) {
    // assert a != null;
    // assert l >= 0;
    // assert r >= l;
    r--;
    int p = Sort_quicksort_findPivotIndex(a, l, r);
    if (p != l) {
        Int32Array_swap(a, p, l);
        p = l;
    }
    while (l < r) {
        while (l < r && a[r] > a[p]) {
            r--;
        }
        while (l < r && a[l] <= a[p]) {
            l++;
        }
        if (l < r) {
            Int32Array_swap(a, l, r);
        }
    }
    if (p != r) {
        Int32Array_swap(a, p, r);
    }
    return r;
}

/**
 * unstable, in-place, average O(n\log_2 n), worst O(n^2)
 */
interface
void Sort_quicksort(int* a, int l, int r) {
    if (l < r - 1) {
        int i = Sort_quicksort_partition(a, l, r);
        Sort_quicksort(a, l, i);
        Sort_quicksort(a, i + 1, r);
    }
}

