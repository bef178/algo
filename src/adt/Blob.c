#include <assert.h>
#include <stdlib.h>
#include <string.h>

Blob * Blob_malloc(const byte * a, const int n) {
    assert(n >= 0);
    Blob * p = calloc(1, sizeof(Blob) + n * sizeof(byte));
    p->n = n;
    memcpy(p->a, a, n);
    return p;
}

void Blob_free(Blob * self) {
    free(self);
}

int Blob_compare(const Blob * self, const Blob * another) {
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
