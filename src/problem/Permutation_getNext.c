/**
 * leetcode#31
 * https://leetcode.com/problems/next-permutation/
 *
 * re-arranges numbers lexicographically into next greater permutation of numbers
 */

static
void OctetArray_swap(byte * a, int i, int j) {
    byte t = a[i];
    a[i] = a[j];
    a[j] = t;
}

void Permutation_getNext(byte * a, int n) {
    // starting from right, find the first a[k] < a[k + 1]
    int k = -1;
    for (int i = n - 2; i >= 0; i--) {
        if (a[i] < a[i + 1]) {
            k = i;
            break;
        }
    }

    if (k != -1) {
        for (int i = n - 1; i > k; i--) {
            if (a[i] > a[k]) {
                OctetArray_swap(a, i, k);
                break;
            }
        }
    }

    for (int i = k + 1, j = n - 1; i < j; i++, j--) {
        OctetArray_swap(a, i, j);
    }
}
