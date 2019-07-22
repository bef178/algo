/**
 * from the lowest bit
 *  if it is 1: set to 0
 *  if it is 0: set to 1 and done
 */
int inc(int i) {
    int mask = 1;
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
