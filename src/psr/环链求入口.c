/**
 * 环链求入口
 *
 * leetcode #142 medium
 * https://leetcode.com/problems/linked-list-cycle-ii/
 */

// 设链首为A，环入口为B。令a=AB。
// 有快指针p2步长为2、慢指针p1步长为1，必相遇于环上，记为C。令b=BC，记环长为c。
// 当p1至B时，p2必然已在环上，两者距离小于环长；p2每次追1，则追及时p1必不会再次经过B，意即p1必不能绕环一周。
// 因此p1走过的距离为a+b；p2走过的距离为a+b+kc。
// 有a+b+kc=2(a+b)，即a=kc-b。
// 即，若另有步长均为1的两指针，分别从A、C起始，将相遇于B。
