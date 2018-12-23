#include <assert.h>
#include <stdlib.h>

int getBit(const byte * stream, int offset) {
    assert(offset >= 0);
    return GET_BITS(stream[offset >> 3], 1 << (7 - (offset & 7)));
}

void setBit(byte * stream, int offset) {
    assert(offset >= 0);
    SET_BITS(stream[offset >> 3], 1 << (7 - (offset & 7)));
}

void clearBit(byte * stream, int offset) {
    assert(offset >= 0);
    CLEAR_BITS(stream[offset >> 3], 1 << (7 - (offset & 7)));
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
