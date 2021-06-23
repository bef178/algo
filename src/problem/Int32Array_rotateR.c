/**
 * leetcode#189
 * https://leetcode.com/problems/rotate-array/
 */
void Int32Array_rotateR(int * a, int l, int r, int k) {
    assert(a != NULL);
    assert(l >= 0);
    assert(r >= l);
    int n = r - l;
    k = k % n;
    if (k < 0) {
        k += n;
    }
    Int32Array_reverse(a, l, r);
    Int32Array_reverse(a, l, l + k);
    Int32Array_reverse(a, l, k, r);
}

/**
 * greatest common divisor
 * the largest positive integer that divides each of the input integers
 */
static
int gcd(int m, int n) {
    assert(m != 0 || n != 0);
    if (m < 0) {
        m = -m;
    }
    if (n < 0) {
        n = -n;
    }
    if (m == 0) {
        return n;
    }
    if (n == 0) {
        return m;
    }
    while (m != n) {
        if (m > n) {
            m -= n;
        } else {
            n -= m;
        }
    }
    return m;
}

static
void Int32Array_rotateR2(int * a, int l, int r, int k) {
    assert(a != NULL);
    assert(l >= 0);
    assert(r >= l);
    a += l;
    int n = r - l;
    k = k % n;
    if (k < 0) {
        k = n + k;
    }
    int g = gcd(k, n);
    if (g == n) {
        return;
    }
    for (int i = 0; i < g; i++) {
        int t = a[i];
        int j = i;
        while (true) {
            int k1 = j - k;
            if (k1 < 0) {
                k1 += n;
            }
            if (k1 == i) {
                break;
            }
            a[j] = a[k1];
            j = k1;
        }
        a[j] = t;
    }
}
