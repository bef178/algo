/**
 * selects the kth smallest(largest) element of an initially unsorted array
 *
 *
 */

/**
 * the median of medians is an approximate (median) selection algorithm,
 * frequently used to supply a good pivot for an exact selection algorithm
 *
 * BFPRT算法在最坏情况下的时间复杂度是O(n)
 * 1. 选取主元
 *  1.1 每5个元素分为一组，多余的舍去
 *  1.2 每组内使用插入排序找到中位数
 *  1.3 对于1.2中找到的所有中位数，调用BFPRT算法求出它们的中位数，作为主元
 * 2. 以1.3选取的主元为分界点，把小于主元的放在左边，大于主元的放在右边
 * 3. 判断主元的位置与k的大小，有选择的对左边或右边递归
 */
int getPivotIndex(int * a, int l, int r);
