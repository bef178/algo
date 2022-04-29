/**
 * 二叉排序树原地转有序双向链表
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static BinaryTreeNode * inplaceConvert(BinaryTreeNode * root) {
    if (root == NULL) {
        return NULL;
    }

    BinaryTreeNode * head = root;
    if (root->l != NULL) {
        head = inplaceConvert(root->l);
        BinaryTreeNode * tail = head;
        while (tail->r != NULL) {
            tail = tail->r;
        }
        tail->r = root;
        root->l = tail;
    }

    root->r = inplaceConvert(root->r);
    if (root->r != NULL) {
        root->r->l = root;
    }

    return head;
}

/**
 * if it is binary search tree, the converted list will be ordered
 *
 * use only l-link and r-link
 */
BinaryTreeNode * BinaryTree_convertToLinkedList(BinaryTreeNode * root) {
    return inplaceConvert(root);
}

void BinaryTree_printAsLinkedList(BinaryTreeNode * head) {
    while (head != NULL && head->r != NULL) {
        printf("%ld ", head->value);
        head = head->r;
    }
    printf("%ld\n", head->value);

    while (head != NULL && head->l != NULL) {
        printf("%ld ", head->value);
        head = head->l;
    }
    printf("%ld\n", head->value);
}
