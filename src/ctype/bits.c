#include <assert.h>
#include <stdlib.h>

static int getBits(byte flags, byte f) {
    return flags & f;
}

static void setBits(byte flags, byte f) {
    flags |= f;
}

static void clearBits(byte flags, byte f) {
    flags &= ~f;
}

int getBit(const void * stream, int offset) {
    assert(stream != NULL);
    assert(offset >= 0);
    const byte * a = (const byte *) stream;
    return getBits(a[offset >> 3], 1 << (7 - (offset & 7))) == 0 ? 0 : 1;
}

void setBit(const void * stream, int offset, int v) {
    assert(stream != NULL);
    assert(offset >= 0);
    assert(v == 0 || v == 1);
    const byte * a = (const byte *) stream;
    if (v == 0) {
        clearBits(a[offset >> 3], 1 << (7 - (offset & 7)));
    } else {
        setBits(a[offset >> 3], 1 << (7 - (offset & 7)));
    }
}

int32 rotateL(int32 mem, int offset) {
    assert(offset >= 0 && offset <= 32);
    return rotateR(mem, 32 - offset);
}

int32 rotateR(int32 mem, int offset) {
    assert(offset >= 0 && offset <= 32);
    return (mem << (32 - offset)) | lshiftR(mem, offset);
}

int32 lshiftR(int32 mem, int offset) {
    assert(offset >= 0 && offset <= 32);
    return (mem >> offset) & ((1 << (32 - offset)) - 1);
}
