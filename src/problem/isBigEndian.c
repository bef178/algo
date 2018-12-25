/**
 * test whether the underlying machine is big-endian
 */
boolean isBigEndian() {
    int n = 1;
    return *((byte *) &n) == 0;
}
