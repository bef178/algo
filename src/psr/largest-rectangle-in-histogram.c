/**
 * Given an int array as heights of histogram's bar height, where the width of each bar is 1. Find the area of the largest rectangle in the histogram.
 *
 * leetcode #84 hard
 * https://leetcode.com/problems/largest-rectangle-in-histogram/
 */

// monotone stack:
int findLargestRectangleArea(int * a, int n) {
    int maxArea = 0;
    int stack[n];
    int stackTop = -1;
    for (int i = 0; i <= n; i++) {
        while (stackTop != -1 && (i == n ? 0 : a[i]) <= a[stack[stackTop]]) {
            int height = a[stack[stackTop--]];
            int r = i - 1;
            int l = stackTop == -1 ? -1 : stack[stackTop]; // (l,r]
            int area = height * (r - l);
            if (maxArea < area) {
                maxArea = area;
            }
        }
        stack[++stackTop] = i;
    }
    return maxArea;
}
