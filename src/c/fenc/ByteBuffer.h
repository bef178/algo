#ifndef _INCLUDED_BYTEBUFFER
#define _INCLUDED_BYTEBUFFER

typedef struct ByteBuffer {
    byte * a;
    int n;
} ByteBuffer;

ByteBuffer * ByteBuffer_malloc(const int capacity);

ByteBuffer * ByteBuffer_mallocCopyBytes(const byte * a, const int n);

void ByteBuffer_free(ByteBuffer * self);

int ByteBuffer_compare(const ByteBuffer * self, const ByteBuffer * another);

#endif // _INCLUDED_BYTEBUFFER
