/**
 * 二叉搜索树原地转有序双向链表
 *
 * leetcode #426 medium
 * https://leetcode.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node * l;
    struct Node * r;
    long value;
} Node;

static Node * inplaceConvert(Node * root) {
    if (root == NULL) {
        return NULL;
    }

    Node * head = root;
    if (root->l != NULL) {
        head = inplaceConvert(root->l);
        Node * tail = head;
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

Node * toLinkedList(Node * root) {
    return inplaceConvert(root);
}

void printLinkedList(Node * head) {
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
