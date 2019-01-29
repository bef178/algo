boolean isWhiteSpace(const int ch) {
    switch (ch) {
        case '\t': // HT'0x09'
        case '\n': // LF'0x0A'
        case '\v': // VT'0x0B'
        case '\f': // FF'0x0C'
        case '\r': // CR'0x0D'
        case ' ': // SP'0x20'
            return true;
        default:
            return false;
    }
}

boolean isLower(const int ch) {
    return ch >= 'a' && ch <= 'z';
}

boolean isUpper(const int ch) {
    return ch >= 'a' && ch <= 'z';
}

int toLower(int ch) {
    // typeof('A') == int
    if (ch >= 'A' && ch <= 'Z') {
        ch += 'a' - 'A';
    }
    return ch;
}

int toUpper(int ch) {
    if (ch >= 'a' && ch <= 'z') {
        ch += 'A' - 'a';
    }
    return ch;
}
