/**
 * Edit distance, a.k.a Levenshtein distance
 *
 * Given two strings s1 and s2, find the minimum number of steps to convert s1 to s2.
 * Only 3 operations are permitted, each counted as 1 step.
 * 1) insertion
 * 2) removal
 * 3) substitution
 *
 * something subtle. "convert s1 to s2" is different from "make s1 the same as s2". the latter implies edit s2 is allowed.
 */

#include <string.h>

static int min(int i, int j, int k) {
    int min = i;
    if (min > j) {
        min = j;
    }
    if (min > k) {
        min = k;
    }
    return min;
}

static const int COST_INSERT = 1;
static const int COST_REMOVE = 1;
static const int COST_MODIFY = 1;

int getEditDistance(byte * s1, int n1, int i1, byte * s2, int n2, int i2) {
    const int COST_INS_OR_DEL = COST_INSERT <= COST_REMOVE ? COST_INSERT : COST_REMOVE;
    while (i1 < n1 && i2 < n2 && s1[i1] == s2[i2]) {
        i1++;
        i2++;
    }

    if (i1 == n1) {
        return (n2 - i2) * COST_INS_OR_DEL;
    } else if (i2 == n2) {
        return (n1 - i1) * COST_INS_OR_DEL;
    }

    return min(
        getEditDistance(s1, n1, i1 + 1, s2, n2, i2) + COST_REMOVE, // remove s1[i1] from s1
        getEditDistance(s1, n1, i1, s2, n2, i2 + 1) + COST_INSERT, // insert s2[i2] into s1
        getEditDistance(s1, n1, i1 + 1, s2, n2, i2 + 1) + COST_MODIFY);
}

int getEditDistance_dp(byte * s1, int n1, byte * s2, int n2) {
    int cost[n1 + 1][n2 + 1];
    cost[0][0] = 0;
    for (int i = 1; i <= n1; i++) {
        cost[i][0] = i * COST_REMOVE;
    }
    for (int j = 1; j <= n2; j++) {
        cost[0][j] = j * COST_INSERT;
    }

    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n2; ++j) {
            if (s1[i] == s2[j]) {
                cost[i + 1][j + 1] = cost[i][j];
            } else {
                cost[i + 1][j + 1] = min(
                    cost[i][j] + COST_MODIFY,
                    cost[i][j + 1] + COST_INSERT,
                    cost[i + 1][j] + COST_REMOVE);
            }
        }
    }
    return cost[n1][n2];
}

#include <assert.h>

void testGetEditDistance() {
    printf("testing getEditDistance ...\n");
    byte * p[][3] = {
        {"aa", "a", "\1"},
        {"aa", "aa", "\0"},
        {"aaa", "a", "\2"},
        {"aaa", "ba", "\2"},
        {"a", "*", "\1"},
        {"a", "b*", "\2"},
    };
    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++) {
        int d1 = getEditDistance(p[i][0], strlen(p[i][0]), 0, p[i][1], strlen(p[i][1]), 0);
        int d2 = getEditDistance_dp(p[i][0], strlen(p[i][0]), p[i][1], strlen(p[i][1]));
        assert(d1 == p[i][2][0]);
        if (d2 != p[i][2][0]) {
            printf("%d %s %ld %s %ld %d\n", i, p[i][0], strlen(p[i][0]), p[i][1], strlen(p[i][1]), d2);
        }
        assert(d2 == p[i][2][0]);
    }
}
