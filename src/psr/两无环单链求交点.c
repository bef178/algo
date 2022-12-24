/**
 * 两无环单链求交点
 *
 * leetcode #160 easy
 * https://leetcode.com/problems/intersection-of-two-linked-lists/
 */

// 都无环时，必有共同的终点。各取链长，相减之，较长者前移差值。之后同时前进，等则为交点
