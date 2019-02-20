static int firstMeet(int * a, int l, int r, int v) {
    r--;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (v == a[m]) {
            return m;
        } else if (v < a[m]) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return -1;
}

search_f * const BinarySearch_firstMeet = &firstMeet;

int BinarySearch_lowerBound(int * a, int l, int r, int v) {
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

int BinarySearch_upperBound(int * a, int l, int r, int v) {
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
