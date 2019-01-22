/**
 * Given api readChunk(), implement read()
 *
 * goog
 */

int readChunk(byte * path, int chunkIndex, byte * buffer) {
    // fake
    return 0;
}

#include <assert.h>
#include <string.h>

static int readChunk2(byte * path, int start, byte * dst, int n) {
    assert(start >= 0);
    assert(n >= 0);

    const int CHUNK_SIZE = 1 << 21; // 2M
    int chunkIndex = start / CHUNK_SIZE;
    int chunkStart = start - chunkIndex * CHUNK_SIZE;

    if (n == 0) {
        return 0;
    } else if (n >= CHUNK_SIZE && chunkStart == 0) {
        return readChunk(path, chunkIndex, dst);
    } else {
        // n < CHUNK_SIZE || chunkStart > 0
        // partial copy
        byte buffer[CHUNK_SIZE];
        int m = readChunk(path, chunkIndex, buffer);
        m -= chunkStart;
        assert(m >= 0);
        n = n < m ? n : m;
        memcpy(dst, buffer, n);
        return n;
    }
}

int read(byte * path, int start, byte * dst, int n) {
    int i = 0;
    while (true) {
        int m = readChunk2(path, start + i, dst + i, n - i);
        i += m;
        if (m == 0) {
            break;
        }
    }
    return i;
}
