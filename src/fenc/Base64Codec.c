/**
 * Base64Codec
 *
 * encoding: byte stream to base64 stream
 * decoding: base64 stream to byte stream
 */

#include <assert.h>
#include <memory.h>
#include <stdlib.h>

static
int * Base64Codec_encoding = NULL;

static
int * Base64Codec_decoding = NULL;

public
void Base64Codec_init() {
    if (Base64Codec_encoding == NULL) {
        Base64Codec_encoding = calloc(64, sizeof(int));
        int k = 0;
        for (int i = 0; i < 26; i++) {
            Base64Codec_encoding[k] = i + 'A';
            k++;
        }
        for (int i = 0; i < 26; i++) {
            Base64Codec_encoding[k] = i + 'a';
            k++;
        }
        for (int i = 0; i < 10; i++) {
            Base64Codec_encoding[k] = i + '0';
            k++;
        }
        Base64Codec_encoding[k++] = '+';
        Base64Codec_encoding[k++] = '/';
    }
    if (Base64Codec_decoding == NULL) {
        Base64Codec_decoding = calloc(128, sizeof(byte));
        memset(Base64Codec_decoding, -1, 128 * sizeof(byte));
        for (int i = 0; i < 64; i++) {
            Base64Codec_decoding[Base64Codec_encoding[i]] = i;
        }
    }
}

/**
 * consume at most 3 bytes, always produce 4 bytes
 * return the number of consumed bytes
 */
static
int encode3byte(byte * src, int i, int j, byte * dst, int k) {
    assert(i >= 0);
    assert(j > i);

    byte k1 = src[i];
    int index1 = (k1 >> 2) & 0x3F;
    dst[k++] = (byte) Base64Codec_encoding[index1];
    int index2 = (k1 & 0x03) << 4;
    if (i + 1 == j) {
        dst[k++] = (byte) Base64Codec_encoding[index2];
        dst[k++] = '=';
        dst[k++] = '=';
        return 1;
    }

    byte k2 = src[i + 1];
    index2 = index2 | ((k2 >> 4) & 0x0F);
    dst[k++] = (byte) Base64Codec_encoding[index2];
    int index3 = (k2 & 0x0F) << 2;
    if (i + 2 == j) {
        dst[k++] = (byte) Base64Codec_encoding[index3];
        dst[k++] = '=';
        return 2;
    }

    byte k3 = src[i + 2];
    index3 = index3 | ((k3 >> 6) & 0x03);
    dst[k++] = (byte) Base64Codec_encoding[index3];
    int index4 = k3 & 0x3F;
    dst[k++] = (byte) Base64Codec_encoding[index4];
    return 3;
}

/**
 * return number of produced bytes
 */
public
int Base64Codec_encode(byte * src, int i, int j, byte * dst, int start) {
    assert(src != NULL);
    assert(i >= 0);
    assert(j >= i);
    assert(dst != NULL);
    assert(start >= 0);

    int k = start;
    while (i < j) {
        int numConsumed = encode3byte(src, i, j, dst, k);
        i += numConsumed;
        k += 4;
    }
    return k - start;
}

/**
 * always consume 4 bytes, produce at most 3 bytes
 * return the number of produced bytes
 */
static
int decode4byte(byte * src, int i, byte * dst, int k) {
    byte k1 = src[i];
    assert(k1 >= 0 && k1 < 128);
    byte k2 = src[i + 1];
    assert(k2 >= 0 && k1 < 128);
    byte k3 = src[i + 2];
    assert(k3 >= 0 && k1 < 128);
    byte k4 = src[i + 3];
    assert(k4 >= 0 && k1 < 128);

    byte v1 = (byte) Base64Codec_decoding[k1];
    assert(v1 >= 0 && v1 < 64);
    byte v2 = (byte) Base64Codec_decoding[k2];
    assert(v2 >= 0 && v2 < 64);
    dst[k++] = (byte) ((v1 << 2) | (v2 >> 4));
    if (k3 == '=') {
        return 1;
    }

    byte v3 = (byte) Base64Codec_decoding[k3]; // '=' => -1
    assert(v3 >= 0 && v3 < 64);
    dst[k++] = (byte) ((v2 << 4) & 0xFF | (v3 >> 2));
    if (k4 == '=') {
        return 2;
    }

    byte v4 = (byte) Base64Codec_decoding[k4];
    assert(v4 >= 0 && v4 < 64);
    dst[k++] = (byte) ((v3 << 6) & 0xFF | v4);
    return 3;
}

/**
 * return number of produced bytes
 */
public
int Base64Codec_decode(byte * src, int i, int j, byte * dst, int start) {
    assert(src != NULL);
    assert(i >= 0);
    assert(j >= i && ((j - i) % 4 == 0));
    assert(dst != NULL);
    assert(start >= 0);

    int k = start;
    while (i < j) {
        int numProduced = decode4byte(src, i, dst, k);
        i += 4;
        k += numProduced;
    }
    return k - start;
}
