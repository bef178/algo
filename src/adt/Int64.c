int Int64_compare(int64 i, int64 j) {
    return i - j;
}

int Int64_getNumberOfBitOne(int64 i) {
    int n = 0;
    while (i != 0) {
        i &= (i - 1);
        n++;
    }
    return n;
}

/**
 * from the lowest bit
 *  if it is 1: set to 0
 *  if it is 0: set to 1 and done
 */
int Int64_inc(int64 i) {
    int64 mask = 1;
    while (mask != 0) {
        if ((i | mask) == i) {
            i &= ~mask;
            mask <<= 1;
        } else {
            i |= mask;
            break;
        }
    }
    return i;
}
