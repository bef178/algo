/**
 * Catalan数，在组合数学中有非常多的应用
 * f(0)=1 \quad and \quad f(n)=\sum_{i=0}^{n-1}f(i)f(n-1-i) \quad for \ n > 0
 * f(0)=1, f(1)=1, f(2)=2, f(3)=5, f(4)=14, f(5)=42, f(6)=132
 */

#include <assert.h>
#include <stdlib.h>

// f(n) = f(0) * f(n - 1) + f(1) * f(n - 2) + ... + f(n - 2) * f(1) + f(n - 1) * f(0)
int64 Catalan_fn(int32 n) {
    assert(n >= 0);
    int64 * a = calloc(n + 1, sizeof(int64));
    a[0] = 1;
    a[1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            a[i] += a[j] * a[i - 1 - j];
        }
    }
    int64 an = a[n];
    free(a);
    return an;
}

// f(n) = C(2n, n) / (n + 1)
int64 Catalan_fn2(int32 n) {
    assert(n >= 0);
    int64 p = 1;
    for (int i = n * 2; i > n + 1; i--) {
        // caution: overflow
        p *= i;
    }
    for (int i = 2; i <= n; i++) {
        p /= i;
    }
    return p;
}

/**
 * 二叉树的异构数
 *
 * 若左子树有i个结点，则右子树有n-1-i个结点
 * f(n) = f(0) * f(n-1) + f(1) * f(n-1-1) + ... + f(n-1) * f(0)
 * 即为卡特兰数
 *
 * Given an integer `n`, return the number of structurally unique BST's (binary search trees) which has exactly n nodes of unique values from 1 to n.
 *
 * leetcode #96 medium
 * https://leetcode.com/problems/unique-binary-search-trees/
 */

/**
 * 有`n`个叶子结点的二叉树有多少种
 *
 * 此二叉树有`n-1`个内部结点的二叉树。即有`n-1`个结点的二叉树的异构数
 */

/**
 * 有n个数依次进入一个栈，求有多少种出栈序列
 *
 * 二叉树的先序序列为结点的入栈顺序，中序序列为结点的出栈顺序。此即为二叉树的异构数。
 */

/**
 * 合法括号排列数
 *
 * 遇到左括号视为一数入栈，遇到匹配的右括号视为此数出栈。此即为n个数的出栈序列数。
 */

/**
 * 给定`n`个顶点的凸多边形，划出若干条互不相交的对角线，把这个多边形划分成了若干个三角形。问有多少种划分
 */

/**
 * 边长为`n`的正方形，从左下到右上，只能向上或向右，问有多少种走法
 */

/**
 * 圆桌握手问题。偶数个人均匀地坐在圆桌边上，某时刻每个人都与另一人握手，手之间不能交叉，问一共有多少种握手方法。
 */

/**
 * Given `n` pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
 *
 * leetcode #22 medium
 * https://leetcode.cn/problems/generate-parentheses/
 */
