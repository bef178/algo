/**
 * since 2010-05-12
 */

#include <assert.h>
#include <stdlib.h>

boolean Utf8_isFirstByte(const byte aByte) {
    return (aByte & 0xc0) != 0x80 && (aByte & 0xfe) != 0xfe;
}

int Utf8_codePointSize(const byte firstByte) {
    assert(Utf8_isFirstByte(firstByte));

    int size = 0;
    while (size < 8 && getBit(&firstByte, size)) {
        ++size;
    }
    if (size == 1 || size > 6) {
        size = 0;  // invalid utf8 head
    } else if (size == 0) {
        ++size;
    }
    return size;
}

/**
 * convert 1 utf8 character to 1 ucs4 character
 * return the size of this @utf8 character
 */
int Utf8_toUcs4(const byte * utf8, int32 * ucs4) {
    assert(utf8 != NULL && ucs4 != NULL);

    int size = Utf8_codePointSize(*utf8);
    switch (size) {
        case 0:
            break;
        case 1:
            *ucs4 = *utf8;
            break;
        default: {
            int32 ch = 0;
            // parse the head
            for (int i = size + 1; i < 8; ++i) {
                ch <<= 1;
                if (getBit(utf8, i)) {
                    ch |= 1;
                }
            }
            // parse the rest
            for (int i = size - 1; i > 0; --i) {
                ++utf8;
                ch <<= 6;
                ch |= *utf8 & 0x3F;
            }
            *ucs4 = ch;
            break;
        }
    }
    return size;
}
