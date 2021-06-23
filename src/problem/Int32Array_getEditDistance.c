/**
 * Edit distance, a.k.a Levenshtein distance
 *
 * Given two strings s1 and s2, find the minimum number of steps to convert s1 to s2.
 * Only 3 operations are permitted, each counted as 1 step.
 * 1) insertion
 * 2) removal
 * 3) substitution
 *
 * kind of subtle. "convert s1 to s2" is different from "make s1 the same as s2", the latter implies s2 is editable.
 *
 * leetcode#72
 * https://leetcode.com/problems/edit-distance/
 */

static const int COST_INSERT = 1;
static const int COST_REMOVE = 1;
static const int COST_MODIFY = 1;

public
int Int32Array_getEditDistance(int * a1, int l1, int r1, int * a2, int l2, int r2) {
    assert(a1 != NULL);
    assert(l1 >= 0);
    assert(r1 >= l1);
    assert(a2 != NULL);
    assert(l2 >= 0);
    assert(r2 >= l2);
    a1 += l1;
    int n1 = r1 - l1;
    a2 += l2;
    int n2 = r2 - l2;
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
            if (a1[i] == a2[j]) {
                cost[i + 1][j + 1] = cost[i][j];
            } else {
                cost[i + 1][j + 1] = Int32_minOf3(
                    cost[i][j] + COST_MODIFY,
                    cost[i][j + 1] + COST_INSERT,
                    cost[i + 1][j] + COST_REMOVE);
            }
        }
    }
    return cost[n1][n2];
}

static
int Int32Array_getEditDistance2(int * a1, int l1, int r1, int * a2, int l2, int r2) {
    const int COST_INS_OR_DEL = COST_INSERT <= COST_REMOVE ? COST_INSERT : COST_REMOVE;
    while (l1 < r1 && l2 < r2 && a1[l1] == a2[l2]) {
        l1++;
        l2++;
    }

    if (l1 == r1) {
        return (r2 - l2) * COST_INS_OR_DEL;
    } else if (l2 == r2) {
        return (r1 - l1) * COST_INS_OR_DEL;
    }

    return Int32_minOf3(
        Int32Array_getEditDistance(a1, l1 + 1, r1, a2, l2, r2) + COST_REMOVE, // remove a1[l1] from a1
        Int32Array_getEditDistance(a1, l1, r1, a2, l2 + 1, r2) + COST_INSERT, // insert a2[l2] into a1
        Int32Array_getEditDistance(a1, l1 + 1, r1, a2, l2 + 1, r2) + COST_MODIFY);
}
