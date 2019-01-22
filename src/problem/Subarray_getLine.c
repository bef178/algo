#include <assert.h>

/**
 * a[l,r)
 * line terminators are any of CR LF, CR, LF, or EOF.
 * return the next index of line terminator, could be @r
 */
int Subarray_getLine(const byte * s, int l, int r) {
    assert(s != NULL);
    assert(l >= 0);
    assert(r >= l);

    int stat = 0;
    int i = l;
    int j = l; // end of "trimmed" data
    while (i < r) {
        switch (stat) {
            case 0: { // not meet a terminator
                int ch = *s++;
                switch (ch) {
                    case CR:
                        stat = 1;
                        j = i++;
                        break;
                    case LF:
                        stat = 2;
                        j = i++;
                        break;
                    case EOF:
                        stat = 2;
                        j = i;
                        break;
                    default:
                        i++;
                        break;
                }
                break;
            }
            case 1: { // meet CR
                int ch = *s++;
                switch (ch) {
                    case LF:
                        stat = 2;
                        i++;
                        break;
                    default:
                        stat = 2;
                        break;
                }
                break;
            }
            case 2: {
                r = i; // trick to break loop
                break;
            }
        }
    }
    // XXX take use of @j
    return i;
}
