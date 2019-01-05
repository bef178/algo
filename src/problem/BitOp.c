/**
 * from the lowest bit
 *  if it is 1: set to 0
 *  if it is 0: set to 1 and done
 */
int BitOp_inc(int x) {
    int mask = 1;
    while (mask != 0) {
        if ((x | mask) == x) {
            x &= ~mask;
            mask <<= 1;
        } else {
            x |= mask;
            break;
        }
    }
    return x;
}

int BitOp_getNumberOfBitOne(int x) {
    int n = 0;
    while (x != 0) {
        x &= (x - 1);
        n++;
    }
    return n;
}
