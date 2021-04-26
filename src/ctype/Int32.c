#include <assert.h>

// spreads the impact of higher bits downward
// openjdk8, java.util.HashMap.hash(Object)
public
int32 Int32_hash(int32 d) {
    return d ^ Int32_shr(d, 16);
}

// jdk6, java.util.HashMap.hash(int)
static
int32 Int32_hash_jdk6(int32 d) {
    d ^= (d >> 20) ^ (d >> 12);
    return d ^ (d >> 7) ^ (d >> 4);
}

// rotate left
public
int32 Int32_rol(int32 d, int numBits) {
    return Int32_ror(d, 32 - numBits);
}

// rotate right
public
int32 Int32_ror(int32 d, int numBits) {
    assert(numBits >= 0 && numBits < 32);
    return (d << (32 - numBits)) | Int32_shr(d, numBits);
}

// rotate right (partial)
public
int32 Int32_rorp(int32 d, int i, int j, int numBits) {
    assert(i >= 0);
    assert(j < 32);
    assert (numBits >= 0 && numBits < j - i);

    int lMask = ~0U << (32 - numBits) >> (32 - numBits);
    int32 l = l = (d >> i) & lMask;
    int hMask = ~0U << (32 - (j - i - numBits)) >> (32 - (j - i - numBits));
    int32 h = (d >> (i + numBits)) & hMask;
    int mask = (~0U << (32 - (j - i)) >> (32 - (j - i))) << i;
    return (d & ~mask) | (l << (j - numBits)) | (h << i);
}

// shift right
public
int32 Int32_shr(int32 d, int numBits) {
    assert(numBits >= 0 && numBits < 32);
    return (d >> numBits) & ((1 << (32 - numBits)) - 1);
}
