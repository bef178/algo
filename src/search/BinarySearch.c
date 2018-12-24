/**
 * return the 1st index of @v
 */
int BinarySearch_search(int * a, int l, int r, int v) {
    r--;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (v == a[m]) {
            // find the 1st
            while (m > 0 && v == a[m - 1]) {
                --m;
            }
            return m;
        } else if (v < a[m]) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return -1;
}

static int upperBound(int * a, int l, int r, int v) {
    while (l < r) {
        int m = (r - l) / 2 + l;
        if (v < a[m]) {
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
        if (v > a[m]) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return r;
}

search_f * const BinarySearch_upperBound = &upperBound;
search_f * const BinarySearch_lowerBound = &lowerBound;
