/**
 * defend against poor quality of user hash function, from jdk6
 */
word Hash_rehash(word hashCode) {
    hashCode ^= (hashCode >> 20) ^ (hashCode >> 12);
    return hashCode ^ (hashCode >> 7) ^ (hashCode >> 4);
}

word Hash_bkdr(const byte * p, const int n) {
    // BKDR hash seed: 31, 131, 1313, 13131, 131313, ...
    // static const int SEED = 31;

    word hashCode = 0;

    const byte * p0 = p;
    const byte * p3 = p + n;
    if ((word) p0 / sizeof(word) == (word) p3 / sizeof(word)) {
        // not cover a cell boundary
        while (p0 < p3) {
            hashCode = (hashCode << 5) - hashCode + *p0++;
        }
    } else {
        const byte * p1 = (const byte *) (((word) p / sizeof(word) + 1) * sizeof(word));
        const word * w1 = (const word *) p1;
        const byte * p2 = (const byte *) (((word) p + n) / sizeof(word) * sizeof(word));
        const word * w2 = (const word *) p2;
        while (p0 < p1) {
            hashCode = (hashCode << 5) - hashCode + *p0++;
        }
        while (w1 < w2) {
            hashCode = (hashCode << 5) - hashCode + *w1++;
        }
        while (p2 < p3) {
            hashCode = (hashCode << 5) - hashCode + *p2++;
        }
    }
    return hashCode;
}

word Hash_djb(const byte * p, const int n) {
    // DJB hash seed: 33
    // static const int SEED = 33;

    word hashCode = 5381;

    const byte * p0 = p;
    const byte * p3 = p + n;
    if ((word) p0 / sizeof(word) == (word) p3 / sizeof(word)) {
        // not cover a cell boundary
        while (p0 < p3) {
            hashCode = (hashCode << 5) + hashCode + *p0++;
        }
    } else {
        const byte * p1 = (const byte *) (((word) p / sizeof(word) + 1) * sizeof(word));
        const word * w1 = (const word *) p1;
        const byte * p2 = (const byte *) (((word) p + n) / sizeof(word) * sizeof(word));
        const word * w2 = (const word *) p2;
        while (p0 < p1) {
            hashCode = (hashCode << 5) + hashCode + *p0++;
        }
        while (w1 < w2) {
            hashCode = (hashCode << 5) + hashCode + *w1++;
        }
        while (p2 < p3) {
            hashCode = (hashCode << 5) + hashCode + *p2++;
        }
    }
    return hashCode;
}
