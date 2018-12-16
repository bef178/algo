static int upperBound(int * a, int l, int r, int v) {
    while (l < r) {
        int m = (r - l) / 2 + l;
        if (a[m] > v) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}

static int lowerBound(int * a, int l, int r, int v) {
    while (l < r) {
        int m = (r - l) / 2 + l;
        if (a[m] < v) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return r;
}

search_f * const BinarySearch_upperBound = &upperBound;
search_f * const BinarySearch_lowerBound = &lowerBound;
