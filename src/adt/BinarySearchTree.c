#include <assert.h>

void BinarySearchTree_add(BinaryTreeNode * root, int64 value) {
    assert(root != NULL);
    if (value < root->value) {
        if (root->l == NULL) {
            root->l = BinaryTreeNode_malloc(value);
        } else {
            BinarySearchTree_add(root->l, value);
        }
    } else {
        if (root->r == NULL) {
            root->r = BinaryTreeNode_malloc(value);
        } else {
            BinarySearchTree_add(root->r, value);
        }
    }
}

/**
 * return the root
 */
void BinarySearchTree_add2(BinaryTreeNode * root, int64 value) {
    assert(root != NULL);
    BinaryTreeNode * p = root;
    while (true) {
        if (value < p->value) {
            if (p->l == NULL) {
                p->l = BinaryTreeNode_malloc(value);
                break;
            } else {
                p = p->r;
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
