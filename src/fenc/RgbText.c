#include <assert.h>

public
int RgbText_getR(int rgb) {
    assert(rgb >= 0 && rgb <= 0xFFFFFF);
    return (rgb >> 16) & 0xFF;
}

public
int RgbText_getG(int rgb) {
    assert(rgb >= 0 && rgb <= 0xFFFFFF);
    return (rgb >> 8) & 0xFF;
}

public
int RgbText_getB(int rgb) {
    assert(rgb >= 0 && rgb <= 0xFFFFFF);
    return rgb & 0xFF;
}

/**
 * always produce 7 bytes
 */
public
void RgbText_encode1unit(int rgb, byte * dst, int start) {
    dst[start] = '#';
    Hexdig_encode1byte(RgbText_getR(rgb), dst, start + 1);
    Hexdig_encode1byte(RgbText_getG(rgb), dst, start + 3);
    Hexdig_encode1byte(RgbText_getB(rgb), dst, start + 5);
}

/**
 * always consume 7 bytes
 */
public
int RgbText_decode1unit(byte * src, int i) {
    assert(src != NULL);
    assert(i >= 0);

    assert(src[i] == '#');
    int r = Hexdig_decode1byte(src, i + 1);
    int g = Hexdig_decode1byte(src, i + 3);
    int b = Hexdig_decode1byte(src, i + 5);
    return (r << 16) | (g << 8) | b;
}
