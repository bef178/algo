/**
 * Escaped
 */

#include <assert.h>
#include <memory.h>
#include <stdlib.h>

static
int * Escaped_encoding = NULL;

static
int * Escaped_decoding = NULL;

public
void Escaped_staticInit() {
    if (Escaped_encoding == NULL) {
        Escaped_encoding = calloc(128, sizeof(int));
        memset(Escaped_encoding, -1, 128 * sizeof(int));
        Escaped_encoding['\0'] = '0';
        Escaped_encoding['\a'] = 'a'; // 0x07
        Escaped_encoding['\b'] = 'b';
        Escaped_encoding['\t'] = 't';
        Escaped_encoding['\n'] = 'n'; // 0x0A
        Escaped_encoding['\v'] = 'v';
        Escaped_encoding['\f'] = 'f';
        Escaped_encoding['\r'] = 'r';
        // Escaped_encoding['\"'] = '\"'; // 0x22
        // Escaped_encoding['\''] = '\''; // 0x27
        Escaped_encoding['\\'] = '\\'; // 0x5C
    }
    if (Escaped_decoding == NULL) {
        Escaped_decoding = calloc(128, sizeof(int));
        memset(Escaped_decoding, -1, 128 * sizeof(int));
        for (int i = 0; i < 128; i++) {
            int key = Escaped_encoding[i];
            if (key > 0) {
                Escaped_encoding[key] = i;
            }
        }
    }
}

static
int Escaped_encode1byte(int aByte, byte * dst, int k) {
    assert(aByte >= 0 && aByte <= 0xFF);
    assert(dst != NULL);
    assert(k >= 0);
    if (aByte >= 0x20 && aByte < 0x7F) {
        dst[k] = aByte;
        return 1;
    } else if (Escaped_encoding[aByte] >= 0) {
        dst[k++] = '\\';
        dst[k] = Escaped_encoding[aByte];
        return 2;
    } else {
        dst[k++] = '\\';
        dst[k++] = 'x';
        HexCodec_encode1byte(aByte, dst, k);
        return 4;
    }
}

public
int Escaped_encode(byte * src, int i, int j, byte * dst, int start) {
    assert(src != NULL);
    assert(i >= 0);
    assert(j >= i);
    assert(dst != NULL);
    assert(start >= 0);

    int k = start;
    while (i < j) {
        int numProduced = Escaped_encode1byte(src[i++] & 0xFF, dst, k);
        k += numProduced;
    }
    return k - start;
}

static
int Escaped_decode1byte(byte * src, int i, byte * outByte) {
    assert(src != NULL);
    assert(i >= 0);
    int aByte = src[i++] & 0xFF;
    if (aByte == '\\') {
        aByte = src[i++] & 0xFF;
        if (aByte == 'x') {
            *outByte = HexCodec_decode1byte(src, i);
            return 4;
        } else if (aByte >= 0x20 && aByte < 0x7F && Escaped_decoding[aByte] >= 0) {
            *outByte = Escaped_decoding[aByte];
            return 2;
        } else {
            // unrecognized escape sequence
            assert(false);
        }
    } else {
        *outByte = aByte;
        return 1;
    }
}

public
int Escaped_decode(byte * src, int i, int j, byte * dst, int start) {
    assert(src != NULL);
    assert(i >= 0);
    assert(j >= i);
    assert(dst != NULL);
    assert(start >= 0);

    int k = start;
    while (i < j) {
        int numConsumed = Escaped_decode1byte(src, i, dst + k);
        i += numConsumed;
        k++;
        assert(i <= j);
    }
    return k - start;
}
