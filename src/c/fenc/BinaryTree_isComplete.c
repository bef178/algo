/**
 * tell it is a complete binary tree or not
 */

boolean BinaryTree_isComplete(BinaryTreeNode * root) {
    LinkedList * p = LinkedList_malloc();
    LinkedList_insert(p, (int64) root);
    boolean meetsNull = false;
    while (!LinkedList_isEmpty(p)) {
        BinaryTreeNode * node = (BinaryTreeNode *) LinkedList_remove(p);
        if (meetsNull) {
            if (node->l != NULL || node->r != NULL) {
                return false;
            }
        } else {
            if (node->l != NULL) {
                LinkedList_insert(p, (int64) node->l);
                if (node->r != NULL) {
                    LinkedList_insert(p, (int64) node->r);
                } else {
                    meetsNull = true;
                }
            } else {
                if (node->r != NULL) {
                    return false;
                } else {
                    meetsNull = true;
                }
            }
        }
    }
    return true;
}
