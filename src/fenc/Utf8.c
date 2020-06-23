/**
 * https://en.wikipedia.org/wiki/UTF-8
 *
 * Treat utf8 as a protocol for integer value to octets.
 * It ranges to 7 bytes, i.e. 36 effective bits, covering entire int32.
 * While, Unicode stops at U+10FFFF, taking 21 effective bits.
 */

#include <assert.h>
#include <stdlib.h>

/**
 * result in [1,7]
 */
static
int Utf8_getNumUtf8Bytes(const int32 ucs4) {
    if (ucs4 < 0) {
        return 7;
    } else if (ucs4 <= 0x7F) {
        return 1;
    } else if (ucs4 <= 0x7FF) {
        return 2;
    } else if (ucs4 <= 0xFFFF) {
        // LE 16-bit
        return 3;
    } else if (ucs4 <= 0x1FFFFF) {
        // LE 21-bit
        return 4;
    } else if (ucs4 <= 0x3FFFFFF) {
        // LE 26-bit
        return 5;
    } else if (ucs4 <= 0x7FFFFFFF) {
        // LE 31-bit
        return 6;
    }
}

static
int Utf8_encode1unit(int32 ucs4, byte * utf8, int start) {
    int n = Utf8_getNumUtf8Bytes(ucs4);
    if (n == 1) {
        utf8[start++] = ucs4;
        return 1;
    }

    int k = start;
    for (int i = 0; i < n; i++) {
        int v = (ucs4 >> ((n - 1 - i) * 6)) & 0x3F;
        if (i == 0) {
            int header = (0xFF << (8 - n)) & 0xFF;
            utf8[k++] = v | header;
        } else {
            utf8[k++] = v | 0x80;
        }
    }
    return k - start;
}

/**
 * a fast encoder without checking content
 */
public
int Utf8_encode(int32 * ucs4, int i, int j, byte * utf8, int start) {
    assert(ucs4 != NULL);
    assert(i >= 0);
    assert(j >= i);
    assert(utf8 != NULL);
    assert(start >= 0);

    int k = start;
    while (i < j) {
        int numProduced = Utf8_encode1unit(ucs4[i], utf8, k);
        i++;
        k += numProduced;
    }
    return k - start;
}

static
boolean Utf8_isUtf8Head(const byte aByte) {
    return (aByte & 0xC0) != 0x80 && (aByte & 0xFE) != 0xFE;
}

static
int Utf8_getNumUtf8BytesByUtf8Head(const byte headByte) {
    assert(Utf8_isUtf8Head(headByte));

    int n = 0;
    while (n < 8 && testSingleBit(&headByte, n)) {
        ++n;
    }
    switch (n) {
        case 0:
            return 1;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            return n;
        default:
            // invalid utf8 head
            return 0;
    }
}

static
int Utf8_decode1unit(byte * utf8, int i, int32 * outUcs4) {
    assert(utf8 != NULL);
    assert(i >= 0);
    assert(outUcs4 != NULL);

    int n = Utf8_getNumUtf8BytesByUtf8Head(utf8[i]);
    switch (n) {
        case 0:
            break;
        case 1:
            *outUcs4 = utf8[i];
            break;
        default: {
            int unheader = 0xFF >> n;
            int32 ucs4 = unheader & utf8[i];
            for (int j = i + 1; j < n; j++) {
                ucs4 = (ucs4 << 6) | (utf8[j] & 0x3F);
            }
            *outUcs4 = ucs4;
            break;
        }
    }
    return n;
}

public
int Utf8_decode(byte * utf8, int i, int j, int32 * ucs4, int start) {
    assert(utf8 != NULL);
    assert(i >= 0);
    assert(j >= i);
    assert(ucs4 != NULL);
    assert(start >= 0);

    int k = start;
    while (i < j) {
        int numConsumed = Utf8_decode1unit(utf8, i, ucs4 + k);
        i += numConsumed;
        k++;
    }
    return k - start;
}
