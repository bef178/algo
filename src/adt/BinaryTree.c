#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

public
typedef LinkNode BinaryTreeNode;

public
BinaryTreeNode * (*BinaryTreeNode_malloc)(int64) = LinkNode_malloc;

public
int64 (*BinaryTreeNode_free)(BinaryTreeNode *) = LinkNode_free;

public
void BinaryTree_free(BinaryTreeNode * root) {
    if (root != NULL) {
        BinaryTree_free(root->l);
        BinaryTree_free(root->r);
        LinkNode_free(root);
    }
}

public
int BinaryTree_size(LinkNode * root) {
    if (root == NULL) {
        return 0;
    }

    int n = 0;
    LinkNode * head = LinkNode_malloc(0);
    LinkNode * rootP = LinkNode_malloc((int64) root);
    LinkNode_enlinkNext(head, rootP);
    while (head->next != NULL) {
        LinkNode * nodeP = LinkNode_delinkNext(head);
        n++;
        BinaryTreeNode * p = (void *) LinkNode_free(nodeP);
        if (p->prev != NULL) {
            LinkNode * nodeP1 = LinkNode_malloc((int64) p->prev);
            LinkNode_enlinkNext(head, nodeP1);
        }
        if (p->next != NULL) {
            LinkNode * nodeP2 = LinkNode_malloc((int64) p->next);
            LinkNode_enlinkNext(head, nodeP2);
        }
    }
    LinkNode_free(head);
    return n;
}

/**
 * the max distance between the root and a leaf
 * empty tree depth = -1
 */
public
int BinaryTree_depth(LinkNode * root) {
    if (root == NULL) {
        return -1;
    }
    int l = BinaryTree_depth(root->l);
    int r = BinaryTree_depth(root->r);
    return (l >= r ? l : r) + 1;
}

/**
 * the distance to the root
 * null => -1
 * root => 0
 */
public
int BinaryTree_getNodeLevel(LinkNode * root, LinkNode * node) {
    assert(node != NULL);

    if (root == NULL) {
        return -1;
    } else if (root == node) {
        return 0;
    }

    int level = BinaryTree_getNodeLevel(root->l, node);
    if (level >= 0) {
        return level + 1;
    }
    level = BinaryTree_getNodeLevel(root->r, node);
    if (level >= 0) {
        return level + 1;
    }
    return -1;
}

public
void BinaryTree_print(LinkNode * root) {
    if (root == NULL) {
        printf("?\n");
        return;
    }

    printf("%ld:", root->value);
    if (root->l == NULL) {
        printf("?");
    } else {
        printf("%ld", root->l->value);
    }
    printf(",");
    if (root->r == NULL) {
        printf("?");
    } else {
        printf("%ld", root->r->value);
    }
    printf("\n");

    BinaryTree_print(root->l);
    BinaryTree_print(root->r);
}
