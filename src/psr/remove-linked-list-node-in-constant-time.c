/**
 * remove given node from a list, in O(1) time
 *
 * 若为尾结点，则需从头遍历一次，worst O(n)
 * 否则，将本结点数据与下一结点数据交换，然后删除下一结点，average O(1)
 *
 * 此解初看很巧妙，但不是正经的工程做法。一旦链表结点被外部引用，则结果不可预料
 */
