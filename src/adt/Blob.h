#ifndef _INCLUDED_BLOB
#define _INCLUDED_BLOB

typedef struct Blob {
    int n;
    byte a[0];
} Blob;

Blob * Blob_malloc(const byte * a, const int n);

void Blob_free(Blob * self);

int Blob_compare(const Blob * self, const Blob * another);

#endif // _INCLUDED_BLOB
