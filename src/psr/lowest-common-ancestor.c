/**
 * Find the lowest common ancestor (LCA) of two given tree nodes.
 * Return `null` when they don't have LCA.
 * Allow a node to be a descendant of itself.
 *
 * 分别向上寻至根，确认根结点相同。起游标，链较长者先步进长度差，之后同时步进，相等时寻得
 * 若不为树而是链表，同理；若链表有环则是另一个故事
 */

#include <assert.h>

static
BinaryTreeNode * BinaryTree_findLowestCommonAncestorInternal(BinaryTreeNode * root, BinaryTreeNode * node1, BinaryTreeNode * node2, boolean * seenNode1, boolean * seenNode2) {
    if (root == NULL) {
        return NULL;
    }

    if (root == node1) {
        *seenNode1 = true;
        return root;
    } else if (root == node2) {
        *seenNode2 = true;
        return root;
    }

    BinaryTreeNode * lcaL = BinaryTree_findLowestCommonAncestorInternal(root->l, node1, node2, seenNode1, seenNode2);
    BinaryTreeNode * lcaR = BinaryTree_findLowestCommonAncestorInternal(root->r, node1, node2, seenNode1, seenNode2);
    if (lcaL != NULL) {
        if (lcaR != NULL) {
            return root;
        }
        return lcaL;
    } else {
        if (lcaR != NULL) {
            return lcaR;
        } else {
            return NULL;
        }
    }
}

/**
 * case: node1 == node2
 * case: node1 is an ancestor of node2
 * case: node1 in tree while node2 not in tree
 */
BinaryTreeNode * BinaryTree_findLowestCommonAncestor(BinaryTreeNode * root, BinaryTreeNode * node1, BinaryTreeNode * node2) {
    assert(node1 != NULL);
    assert(node2 != NULL);

    if (node1 == node2) {
        return node1;
    }

    boolean seenNode1 = false;
    boolean seenNode2 = false;
    BinaryTreeNode * lca = BinaryTree_findLowestCommonAncestorInternal(root, node1, node2, &seenNode1, &seenNode2);
    if (lca == NULL) {
        // neither is in tree
        return NULL;
    } else if (seenNode1 && seenNode2) {
        return lca;
    } else {
        BinaryTreeNode * other = lca == node1 ? node2 : node1;
        if (BinaryTree_containsNode(lca, other)) {
            return lca;
        } else {
            // the other is not in tree
            return NULL;
        }
    }
}
