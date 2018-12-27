/**
 * 前中序建树
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

BinaryTreeNode * build(const byte * preOrder, const byte * inOrder, const int n) {
    assert(preOrder != NULL);
    assert(inOrder != NULL);

    if (n == 0) {
        return NULL;
    }

    BinaryTreeNode * node = BinaryTreeNode_malloc(*preOrder);

    byte * t = memchr(inOrder, *preOrder, n);
    if (t == NULL) {
        loge(E_INVALID_ARGUMENT);
        exit(-1);
    }
    int sizeL = t - inOrder;
    int sizeR = n - 1 - sizeL;

    node->l = build(preOrder + 1, inOrder, sizeL);
    node->r = build(preOrder + 1 + sizeL, inOrder + sizeL + 1, sizeR);

    return node;
}
