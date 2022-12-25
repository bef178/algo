#include <assert.h>
#include <stdlib.h>
#include <string.h>

public
ByteBuffer * ByteBuffer_malloc(const int capacity) {
    assert(capacity >= 0);
    ByteBuffer * self = calloc(1, sizeof(ByteBuffer));
    self->a = calloc(capacity, sizeof(byte));
    self->n = capacity;
    return self;
}

public
ByteBuffer * ByteBuffer_mallocCopyBytes(const byte * a, const int n) {
    assert(a != NULL);
    assert(n >= 0);
    ByteBuffer * self = ByteBuffer_malloc(n);
    memcpy(self->a, a, n);
    return self;
}

public
void ByteBuffer_free(ByteBuffer * self) {
    free(self->a);
    free(self);
}

public
int ByteBuffer_compare(const ByteBuffer * self, const ByteBuffer * another) {
    if (another == NULL) {
        return (int64) self;
    }
    if (self == another) {
        return 0;
    }
    int result = memcmp(self->a, another->a, (self->n <= another->n ? self->n : another->n));
    if (result != 0) {
        return result;
    }
    if (self->n != another->n) {
        return self->n - another->n;
    }
    return 0;
}
