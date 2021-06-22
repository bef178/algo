/**
 * leetcode#84
 * https://leetcode.com/problems/largest-rectangle-in-histogram/
 *
 * Given an int array as heights of histogram's bar height, where the width of each bar is 1. Find the area of the largest rectangle in the histogram.
 */

// monotone stack:
int largestRectangleArea(int * heights, int width) {
    int maxArea = 0;
    int stack[width];
    int stackTop = -1;
    for (int i = 0; i <= width; i++) {
        while (stackTop != -1 && (i == width ? 0 : heights[i]) <= heights[stack[stackTop]]) {
            int height = heights[stack[stackTop--]];
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
