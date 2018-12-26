#include <assert.h>

/**
 * read one line from @src to @dst
 * read at most @n bytes
 * always copy line terminators
 * return number of actual bytes copied
 */
int getLine(byte * dst, const byte * src, const int n) {
    assert(dst != NULL);
    assert(src != NULL);
    assert(n >= 0);

    int stat = 0;
    byte * dst1 = dst + n;
    while (dst < dst1) {
        switch (stat) {
            case 0: {
                int ch = *src++;
                switch (ch) {
                    case CR:
                        stat = 1;
                        *dst++ = ch;
                        break;
                    case LF:
                        stat = 2;
                        *dst++ = ch;
                        break;
                    case EOF:
                        stat = 2;
                        src--;
                        break;
                    default:
                        *dst++ = ch;
                        break;
                }
                break;
            }
            case 1: {
                int ch = *src++;
                switch (ch) {
                    case LF:
                        stat = 2;
                        *dst++ = ch;
                        break;
                    default:
                        src--;
                        stat = 2;
                        break;
                }
                break;
            }
            case 2: {
                return dst - (dst1 - n);
            }
        }
    }
}
