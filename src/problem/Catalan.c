/**
 * Catalan数，在组合数学中有非常多的应用
 * f(0)=1 \quad and \quad f(n+1)=\sum_{i=0}^{n}f(i)f(n-i) \quad for \ n \ge 0
 * f(0)=1, f(1)=1, f(2)=2, f(3)=5, f(4)=14, f(5)=42, f(6)=132
 */

#include <stdlib.h>

// f(n) = f(0) * f(n - 1) + f(1) * f(n - 2) + ... + f(n - 2) * f(1) + f(n - 1) * f(0)
// also f(n) = C(2n, n) / (n + 1)
int Catalan_calculate2(int n) {
    int * a = calloc(n + 1, sizeof(int));
    a[0] = 1;
    a[1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            a[i] += a[j] * a[i - 1 - j];
        }
    }
    int an = a[n];
    free(a);
    return an;
}

/**
 * 二叉树的异构数
 * Given n, how many structurally unique BSTs (binary search trees) that store values 1..n?
 * For example, given n = 3, there are a total of 5 unique BSTs.
 */

/**
 * n个结点的异构二叉树数 <==> n对括号的合法序列数
 * 可以想像有n+1个数作为二叉树的叶结点，括起2数即增1内部结点
 * 推导出通项公式即可证明
 */
