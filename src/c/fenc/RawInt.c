/**
 * RawInt
 *
 * big int as stream, big-endian, bytes[0] is the highest segment
 */

#include <assert.h>
#include <memory.h>
#include <stdlib.h>

const int NUM_BITS_PER_BYTE = 8;

public
int RawInt_getEffectiveStartIndex(byte * a, int i, int j) {
    byte autofill = (a[i] >= 0) ? 0 : -1;
    for (int k = i; k < j; k++) {
        if (a[k] == autofill) {
            continue;
        }
        if ((a[k] >= 0) == (autofill >= 0)) {
            return k;
        } else {
            return k - 1;
        }
    }
    return j - 1;
}

public
int RawInt_cmp(byte * one, int oneStart, int oneEnd,
        byte * another, int anotherStart, int anotherEnd) {
    int p = RawInt_getEffectiveStartIndex(one, oneStart, oneEnd);
    int oneLen = oneEnd - p;
    one += p;

    int q = RawInt_getEffectiveStartIndex(another, anotherStart, anotherEnd);
    int anotherLen = anotherEnd - q;
    another += q;

    if ((one[0] >= 0) != (another[0] >= 0)) {
        // different sign
        return (one[0] < another[0]) ? -1 : 1;
    }

    if (oneLen != anotherLen) {
        return ((oneLen < anotherLen) == (one[0] >= 0)) ? -1 : 1;
    }

    int result = memcmp(one, another, oneLen);
    if (result < 0) {
        return -1;
    } else if (result == 0) {
        return 0;
    } else {
        return 1;
    }
}

public
int RawInt_cmp8(byte * a, int i, int j, int64 value) {
    byte bytes[8];
    RawInt_mov8(bytes, 0, 8, value);
    return RawInt_cmp(a, i, j, bytes, 0, 8);
}

public
void RawInt_mov(byte * dst, int dstStart, int dstEnd, byte * src, int srcStart, int srcEnd)  {
    int dstSize = dstEnd - dstStart;
    int srcSize = srcEnd - srcStart;
    int n = srcSize <= dstSize ? srcSize : dstSize;
    memcpy(dst + (dstEnd - n), src + (srcEnd - n), n);
    if (dstSize > srcSize) {
        byte autofill = src[srcStart] >= 0 ? 0 : -1;
        memset(dst, autofill, dstSize - srcSize);
    }
}

public
void RawInt_mov8(byte * a, int i, int j, int64 value) {
    for (int k = j - 1; k >= i; k--) {
        a[k] = value & 0xFF;
        value >>= 8;
    }
}

public
int64 RawInt_toInt64(byte * a, int i, int j) {
    const int NUM_BYTES_PER_INT64 = 64 / 8;
    int64 value = (a[i] >= 0) ? 0 : -1;
    int i1 = j - i <= NUM_BYTES_PER_INT64 ? i : j - NUM_BYTES_PER_INT64;
    for (int k = i1; k < j; k++) {
        value = (value << 8) | (a[k] & 0xFF);
    }
    return value;
}

public
void RawInt_print(byte * a, int i, int j) {
    printf("0x");
    for (int k = i; k < j; k++) {
        printf("%02X", a[k] & 0xFF);
    }
    printf("\n");
}
