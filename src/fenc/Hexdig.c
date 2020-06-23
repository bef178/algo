/**
 * Hexdig
 *
 * encoding: 0x3FD4 => "3FD4"
 * decoding: base64 stream to byte stream
 */

#include <assert.h>

static
int encode4bit(int value) {
    switch (value) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            return value + '0';
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            return value + 'A';
        default:
            break;
    }
    assert(false);
}

/**
 * always produce 2 bytes
 */
public
void Hexdig_encode1byte(int aByte, byte * dst, int k) {
    assert(aByte >= 0 && aByte <= 0xFF);
    assert(dst != NULL);
    assert(k >= 0);
    dst[k++] = encode4bit((aByte >> 4) & 0x0F);
    dst[k] = encode4bit(aByte & 0x0F);
}

static
int decode4bit(int ch) {
    switch (ch) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return ch - '0';
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
            return ch - 'A' + 10;
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
            return ch - 'a' + 10;
        default:
            break;
    }
    assert(false);
}

/**
 * always consume 2 bytes
 */
public
int Hexdig_decode1byte(byte * src, int i) {
    byte aByte = decode4bit(src[i++]);
    aByte = (aByte << 4) | decode4bit(src[i]);
    return aByte;
}
