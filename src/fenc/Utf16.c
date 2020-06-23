#include <assert.h>

static
boolean Utf16_isHeadSurrogate(int16 codeUnit) {
    return codeUnit >= 0xDC00 && codeUnit <= 0xDFFF;
}

static
boolean Utf16_isTailSurrogate(int16 codeUnit) {
    return codeUnit >= 0xD800 && codeUnit <= 0xDBFF;
}

public
int Utf16_encodeBigEndian(int32 codepoint, int16 * dst, int start) {
    assert(codepoint >= 0);
    if (codepoint <= 0xD7FF) {
        dst[start] = (int16) codepoint;
        return 1;
    } else if (codepoint <= 0xDFFF) {
        assert(false);
    } else if (codepoint <= 0xFFFF) {
        dst[start] = (int16) codepoint;
        return 1;
    } else if (codepoint <= 0x10FFFF) {
        // 20 bits in [0, 0x0FFFFF]
        int32 x = codepoint - 0x010000;
        dst[start++] = (x >> 10) & 0x03FF | 0xD800;
        dst[start] = x & 0x03FF | 0xDC00;
        return 2;
    } else {
        assert(false);
    }
}

public
int Utf16_decodeBigEndian(int16 * src, int i, int32 * outCodepoint) {
    assert(src != NULL);
    assert(i >= 0);
    assert(outCodepoint != NULL);

    if (Utf16_isTailSurrogate(src[i])) {
        assert(false);
    } else if (!Utf16_isHeadSurrogate(src[i])) {
        *outCodepoint = src[i];
        return 1;
    } else if (!Utf16_isTailSurrogate(src[i + 1])) {
        assert(false);
    } else {
        int32 x = src[0] & 0xFFFF & ~0xD800;
        x = (x << 10) | (src[1] & 0xFFFF & ~0xDC00);
        *outCodepoint = x + 0x010000;
        return 2;
    }
}