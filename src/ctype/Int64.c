#include <assert.h>

// spreads the impact of higher bits downward
// openjdk8, java.util.HashMap.hash(Object)
int32 hash(int32 i) {
    return i ^ shr(i, 16);
}

// jdk6, java.util.HashMap.hash(int)
int32 hash6(int32 i) {
    i ^= (i >> 20) ^ (i >> 12);
    return i ^ (i >> 7) ^ (i >> 4);
}

int32 rol(int32 d, int offset) {
    return ror(d, 32 - offset);
}

int32 ror(int32 d, int offset) {
    assert(offset >= 0 && offset <= 32);
    return (d << (32 - offset)) | shr(d, offset);
}

int32 rorp(int32 d, int i, int j, int offset) {
    assert(i >= 0);
    assert (offset >= 0 && offset <= j - i);

    int lMask = ~0U << (32 - offset) >> (32 - offset);
    int32 l = l = (d >> i) & lMask;
    int hMask = ~0U << (32 - (j - i - offset)) >> (32 - (j - i - offset));
    int32 h = (d >> (i + offset)) & hMask;
    int mask = (~0U << (32 - (j - i)) >> (32 - (j - i))) << i;
    return (d & ~mask) | (l << (j - offset)) | (h << i);
}

int32 shr(int32 d, int offset) {
    assert(offset >= 0 && offset <= 32);
    return (d >> offset) & ((1 << (32 - offset)) - 1);
}

int Int64_compare(int64 i, int64 j) {
    return i - j;
}

int32 Int64_hash(int64 d) {
    int32 h = (d >> 32) & 0xFFFFFFFF;
    int32 l = d & 0xFFFFFFFF;
    return hash(h) ^ hash(l);
}
