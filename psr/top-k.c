/**
 * Given an int array, find the k-th largest(smallest) element
 *
 * leetcode #215 medium
 * https://leetcode.com/problems/kth-largest-element-in-an-array/
 */

/**
 * 有很多应用场景需要求前k大的数，这类问题称为top-k问题。这个问题的解法也可解决求第k大的数。
 * 步骤
 *  1. 选取pivot。一般选第一个或最后一个或最中间的那个。
 *  2. 移动数组元素，使得小于等于pivot的元素都在它左侧，大于它的都在它右侧
 *  3. 比较pivot的索引值与k，选择它的左段或右段进行递归
 * 以上就是quickselect算法。因pivot是随机选取的，时间复杂度可能退化到O(n^2)。
 *
 * the median of medians is an approximate (median) selection algorithm, frequently used to supply a good pivot for an exact selection algorithm, mainly the quickselect. It is sometimes called BFPRT after the last names of the authors.
 *  1.1 每5个元素分为一组，多余的舍去
 *  1.2 每组内使用插入排序找到中位数
 *  1.3 对于1.2中找到的所有中位数，调用BFPRT算法求出它们的中位数，作为pivot
 */

/**
 * return the index of pivot
 */
int bfprt(int * a, int l, int r);


#include <assert.h>

static
int partition(int * a, int l, int r) {
    int p = l; // pivot
    r--;
    while (l < r) {
        while (l < r && a[r] > a[p]) {
            r--;
        }
        while (l < r && a[l] <= a[p]) {
            l++;
        }
        if (l < r) {
            Int32Array_swap(a, l, r);
        }
    }
    if (p != r) {
        Int32Array_swap(a, p, r);
    }
    return r;
}

public
int findKthSmallest(int * a, int l, int r, int k) {
    assert(a != NULL);
    assert(l >= 0);
    assert(r >= l);
    assert(k >= 0 && k < r - l);
    a += l;
    int n = r - l;
    int p = -1;
    while ((p = partition(a, 0, n)) != k) {
        if (p < k) {
            a += p + 1;
            n -= p + 1;
            k -= p + 1;
        } else {
            n = p;
        }
    }
    return a[k];
}
