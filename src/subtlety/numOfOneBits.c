int numOfOneBits(int i) {
    int n = 0;
    while (i != 0) {
        i &= i - 1;
        n++;
    }
    return n;
}
