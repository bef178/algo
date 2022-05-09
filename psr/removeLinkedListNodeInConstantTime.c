/**
 * remove given node from a list, in O(1) time
 *
 * 若为尾结点，则需从头遍历一次，worst O(n)
 * 否则，将本结点数据与下一结点数据交换，然后删除下一结点，average O(1)
 *
 * 这个解法初看很巧妙；一旦有其它指针指向链表中的结点，则结果不可预料
 * 不是正经的工程做法
 */

void removeNodeInConstantTime(LinkedListNode * head, LinkedListNode * target) {
}
