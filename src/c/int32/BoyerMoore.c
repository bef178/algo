/**
 * 字符串匹配 Boyer Moore 算法
 *
 * https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm
 *
 * - 左对齐然后从模式串的右端开始比对
 * - 坏字符
 *   - 主串中失配处的字符称为坏字符
 *   - 若整体能匹配，则坏字符处应亦能匹配。因此，将模式串向右「滑动」，使得坏字符处能匹配，再重新比对
 * - 好后缀
 *   - 失配时，已有匹配的部分称为好后缀
 *   - 失配时，若好后缀存在，同样将模式串向右移动使得好后缀能匹配，再重新比对
 * - 坏字符与好后缀的滑动距离只与模式串有关，与主串无关
 * - 坏字符与好后缀相互独立，实践时取两者之最大值
 */

#include <assert.h>
#include <memory.h>

static
const int CHARSET_SIZE = 256;

static
void calcBadCharacterTable(const byte * p, const int pLen, int * jumpTable) {
    for (int i = 0; i < CHARSET_SIZE; i++) {
        jumpTable[i] = pLen;
    }
    const int lastIndex = pLen - 1;
    for (int i = 0; i < lastIndex; i++) {
        int value = p[i] & 0xFF;
        jumpTable[p[i] & 0xFF] = lastIndex - i;
    }
}

static
int findLongestCommonSuffixLength(const byte * s1, const int s1Len, const byte * s2, const int s2Len) {
    int i = 0;
    while (i < s1Len && i < s2Len) {
        if (s1[s1Len - 1 - i] != s2[s2Len - 1 - i]) {
            break;
        }
        i++;
    }
    return i;
}

static
void calcGoodSuffixTableWhenRepeatIsPrefix(const byte * p, const int pLen, int * jumpTable) {
    // 好后缀不存在时，移动1
    jumpTable[pLen - 1] = 1;

    int lastSuffixLen = 0;
    for (int i = 1; i < pLen; i++) {
        int suffixStart = pLen - i;
        int repeatLen;
        if (memcmp(p, p + suffixStart, i) == 0) {
            repeatLen = i;
            lastSuffixLen = repeatLen;
        } else {
            repeatLen = lastSuffixLen;
        }
        jumpTable[suffixStart - 1] = pLen + i - repeatLen;
    }
}

static
void calcGoodSuffixTableWhenRepeatIsNotPrefix(const byte * p, const int pLen, int * jumpTable) {
    for (int i = 1; i < pLen; i++) {
        // p的每个前缀
        int suffixLen = findLongestCommonSuffixLength(p, pLen, p, i);
        if (suffixLen > 0) {
            int repeatStart = i - suffixLen;
            jumpTable[pLen - suffixLen - 1] = pLen - repeatStart;
        }
    }
}

static
void calcGoodSuffixTable(const byte * p, const int pLen, int * jumpTable) {
    calcGoodSuffixTableWhenRepeatIsPrefix(p, pLen, jumpTable);
    calcGoodSuffixTableWhenRepeatIsNotPrefix(p, pLen, jumpTable);
}

public
int BoyerMoore_find(byte * s, int sLen, byte * p, int pLen) {
    assert(s != NULL && sLen >= 0);
    assert(p != NULL && pLen >= 0);

    if (pLen == 0) {
        return 0;
    }
    if (sLen == 0) {
        return -1;
    }
    if (pLen > sLen) {
        return -1;
    }

    int badCharacterTable[CHARSET_SIZE];
    calcBadCharacterTable(p, pLen, badCharacterTable);

    int goodSuffixTable[pLen];
    calcGoodSuffixTable(p, pLen, goodSuffixTable);

    int i = pLen - 1;
    while (i < sLen) {
        // compare from right to left
        int j = pLen - 1;
        while (j >= 0 && p[j] == s[i]) {
            i--;
            j--;
        }
        if (j < 0) {
            return i + 1;
        }

        i += Int32_max(badCharacterTable[s[i]], goodSuffixTable[j]);
    }
    return -1;
}
