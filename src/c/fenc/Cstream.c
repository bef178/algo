/**
 * Cstream accept void stream or byte stream standing for general data
 * but not an array of specific struct of int etc.
 */

#include <assert.h>
#include <stdlib.h>

static
void setBits_onByte(byte bits, byte mask, boolean value) {
    if (value) {
        bits |= mask;
    } else {
        bits &= ~mask;
    }
}

static
int testBits_onByte(byte bits, byte mask) {
    return bits & mask;
}

public
void Cstream_setSingleBit(const void * p, int offset, boolean value) {
    assert(p != NULL);
    assert(offset >= 0);
    const byte * a = (const byte *) p;
    setBits_onByte(a[offset >> 3], 1 << (7 - (offset & 7)), value);
}

public
boolean Cstream_testSingleBit(const void * p, int offset) {
    assert(p != NULL);
    assert(offset >= 0);
    const byte * a = (const byte *) p;
    return testBits_onByte(a[offset >> 3], 1 << (7 - (offset & 7))) != 0 ? true : false;
}


public
int32 Cstream_hash_bkdr(const byte * p, const int n) {
    // BKDR hash seed: 31, 131, 1313, 13131, 131313, ...
    // hashCode = hashCode * SEED + i;

    int32 hashCode = 0;
    const byte * p1 = p + n;
    while (p < p1) {
        hashCode = (hashCode << 5) - hashCode + (0xFF & *p++);
    }
    return hashCode;
}

public
int32 Cstream_hash_djb(const byte * p, const int n) {
    // DJB hash seed: 5381
    // hashCode = hashCode * 33 + i static const int SEED = 33;

    int32 hashCode = 5381;
    const byte * p1 = p + n;
    while (p < p1) {
        hashCode = (hashCode << 5) + hashCode + (0xFF & *p++);
    }
    return hashCode;
}
