/**
 * increase
 *
 * from the lowest bit
 *  if it is 1: set to 0
 *  if it is 0: set to 1 and done
 */

int inc(int n) {
    int mask = 1;
    while (mask != 0) {
        if ((n | mask) == n) {
            n &= ~mask;
            mask <<= 1;
        } else {
            n |= mask;
            break;
        }
    }
    return n;
}
