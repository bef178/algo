/**
 * 前中序建树
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

BinaryTreeNode * BinaryTree_fromPreorderAndInorder(const byte * preorder, const byte * inorder, const int n) {
    assert(preorder != NULL);
    assert(inorder != NULL);

    if (n == 0) {
        return NULL;
    }

    BinaryTreeNode * node = BinaryTreeNode_malloc(*preorder);

    byte * t = memchr(inorder, *preorder, n);
    if (t == NULL) {
        loge(E_INVALID_ARGUMENT);
        exit(-1);
    }
    int sizeL = t - inorder;
    int sizeR = n - 1 - sizeL;

    node->l = BinaryTree_fromPreorderAndInorder(preorder + 1, inorder, sizeL);
    node->r = BinaryTree_fromPreorderAndInorder(preorder + 1 + sizeL, inorder + sizeL + 1, sizeR);

    return node;
}
