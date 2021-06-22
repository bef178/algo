public
int Int64_compare(int64 i, int64 j) {
    return i - j;
}

public
int32 Int64_hash(int64 i) {
    int32 h = (i >> 32) & 0xFFFFFFFF;
    int32 l = i & 0xFFFFFFFF;
    return Int32_hash(h) ^ Int32_hash(l);
}
