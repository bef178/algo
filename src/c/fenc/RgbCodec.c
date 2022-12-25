#include <assert.h>

public
int RgbCodec_getR(int rgb) {
    assert(rgb >= 0 && rgb <= 0xFFFFFF);
    return (rgb >> 16) & 0xFF;
}

public
int RgbCodec_getG(int rgb) {
    assert(rgb >= 0 && rgb <= 0xFFFFFF);
    return (rgb >> 8) & 0xFF;
}

public
int RgbCodec_getB(int rgb) {
    assert(rgb >= 0 && rgb <= 0xFFFFFF);
    return rgb & 0xFF;
}

/**
 * 0xFF0000 => "#FF0000"
 * always produce 7 bytes
 */
public
void RgbCodec_encode1unit(int rgb, byte * dst, int start) {
    dst[start] = '#';
    HexCodec_encode1byte(RgbCodec_getR(rgb), dst, start + 1);
    HexCodec_encode1byte(RgbCodec_getG(rgb), dst, start + 3);
    HexCodec_encode1byte(RgbCodec_getB(rgb), dst, start + 5);
}

/**
 * always consume 7 bytes
 */
public
int RgbCodec_decode1unit(byte * src, int i) {
    assert(src != NULL);
    assert(i >= 0);

    assert(src[i] == '#');
    int r = HexCodec_decode1byte(src, i + 1);
    int g = HexCodec_decode1byte(src, i + 3);
    int b = HexCodec_decode1byte(src, i + 5);
    return (r << 16) | (g << 8) | b;
}
