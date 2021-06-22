#include <assert.h>

static
void RawInt_shiftL(byte * a, int i, int j, int numBits) {
    assert(a != NULL);
    assert(i >= 0);
    assert(j >= i);
    assert(numBits >= 0);
    a += i;
    int n = j - i;
    int p = numBits / 8;
    if (p > 0) {
        for (int k = 0; k < n - p; k++) {
            a[k] = a[k + p];
        }
        for (int k = n - p; k < n; k++) {
            a[k] = 0;
        }
    }
    int q = numBits % 8;
    if (q > 0) {
        byte mask = -1 << q; // when q = 2, mask = 1111 1100
        byte cb = 0; // not true carry-byte
        for (int k = n - 1 - p; k >= 0; k--) {
            // 12345678 => 345678__, ______12
            byte value = a[k];
            a[k] = (value << q) | cb;
            cb = (value >> (8 - q)) & ~mask;
        }
    }
}

static
void RawInt_shiftR(byte * a, int i, int j, int numBits, boolean isSigned) {
    assert(a != NULL);
    assert(i >= 0);
    assert(j >= i);
    assert(numBits >= 0);
    a += i;
    int n = j - i;
    byte autofill = isSigned ? (a[0] >= 0 ? 0 : -1) : 0;
    int p = numBits / 8;
    if (p > 0) {
        for (int k = n - 1; k >= p; k--) {
            a[k] = a[k - p];
        }
        for (int k = p - 1; k >= 0; k--) {
            a[k] = autofill;
        }
    }
    int q = numBits % 8;
    if (q > 0) {
        byte mask = (1 << (8 - q)) - 1; // when q = 2, mask = 0011 1111
        byte cb = autofill & ~mask;
        for (int k = p; k < n; k++) {
            // 12345678 => __123456, 78______
            byte value = a[k];
            a[k] = (value >> q) & mask | cb;
            cb = value << (8 - q);
        }
    }
}

public
void RawInt_shl(byte * a, int i, int j, int numBits) {
    RawInt_shiftL(a, i, j, numBits);
}

public
void RawInt_shr(byte * a, int i, int j, int numBits) {
    RawInt_shiftR(a, i, j, numBits, false);
}

/**
 * shift arithmetic left
 */
public
void RawInt_sal(byte * a, int i, int j, int numBits) {
    RawInt_shiftL(a, i, j, numBits);
}

public
void RawInt_sar(byte * a, int i, int j, int numBits) {
    RawInt_shiftR(a, i, j, numBits, true);
}
