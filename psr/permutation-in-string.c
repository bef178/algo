/**
 * Given two strings `s` and `s1`, return `true` if `s` contains a permutation of `s1`.
 *
 * leetcode #567 medium
 * https://leetcode.com/problems/permutation-in-string/
 */

boolean checkInclusion(int * s, int n, int * s1, int n1) {
    int s1counts[26] = { 0 };
    for (int i = 0; i < n1; i++) {
        s1counts[s1[i] - 'a']++;
    }
    // [l,r]
    int r = 0;
    for (int l = 0; l <= n - n1; l++) {
        while (r < l + n1 && s1counts[s[r] - 'a'] > 0) {
            s1counts[s[r] - 'a']--;
            r++;
        }
        if (r == l + n1) {
            return true;
        }
        s1counts[s[l] - 'a']++;
    }
    return false;
}
