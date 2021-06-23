#include <assert.h>

/**
 * leetcode#701
 * https://leetcode.com/problems/insert-into-a-binary-search-tree/
 *
 * return the root
 */
BinaryTreeNode * BinarySearchTree_add(BinaryTreeNode * root, int64 value) {
    if (root == NULL) {
        return BinaryTreeNode_malloc(value);
    }

    BinaryTreeNode * p = root;
    while (true) {
        if (value < p->value) {
            if (p->l == NULL) {
                p->l = BinaryTreeNode_malloc(value);
                break;
            } else {
                p = p->l;
            }
        } else {
            if (p->r == NULL) {
                p->r = BinaryTreeNode_malloc(value);
                break;
            } else {
                p = p->r;
            }
        }
    }
}

/**
 *      u               w
 *     / \             / \
 *    w   c     =>    a   u
 *   / \                 / \
 *  a   b               b   c
 *
 * return the new root; pending join parent and new root
 */
BinaryTreeNode * BinarySearchTree_rotateR(BinaryTreeNode * u) {
    assert(u != NULL);
    BinaryTreeNode * w = u->l;
    assert(w != NULL);
    u->l = w->r;
    w->r = u;
    return w;
}
