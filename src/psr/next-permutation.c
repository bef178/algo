/**
 * re-arranges numbers lexicographically into next greater permutation of numbers
 *
 * leetcode #31 medium
 * https://leetcode.com/problems/next-permutation/
 */

static
void ByteArray_swap(byte * a, int i, int j) {
    byte t = a[i];
    a[i] = a[j];
    a[j] = t;
}

void findNextPermutation(byte * a, const int aLen) {
    // starting from right, find the first a[k] < a[k + 1]
    int k = -1;
    for (int i = aLen - 2; i >= 0; i--) {
        if (a[i] < a[i + 1]) {
            k = i;
            break;
        }
    }

    if (k != -1) {
        for (int i = aLen - 1; i > k; i--) {
            if (a[i] > a[k]) {
                ByteArray_swap(a, i, k);
                break;
            }
        }
    }

    for (int i = k + 1, j = aLen - 1; i < j; i++, j--) {
        ByteArray_swap(a, i, j);
    }
}
