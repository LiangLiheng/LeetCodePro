#
# @lc app=leetcode id=2807 lang=java
#
# [2807] Insert Greatest Common Divisors in Linked List
#
# @lc code=start
/**
* Definition for singly-linked list.
* public class ListNode {
*     int val;
*     ListNode next;
*     ListNode() {}
*     ListNode(int val) { this.val = val; }
*     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
* }
*/
class Solution {
    private int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    public ListNode insertGreatestCommonDivisors(ListNode head) {
        if (head == null || head.next == null) return head;
        ListNode curr = head;
        while (curr != null && curr.next != null) {
            int gcdVal = gcd(curr.val, curr.next.val);
            ListNode newNode = new ListNode(gcdVal);
            newNode.next = curr.next;
            curr.next = newNode;
            curr = newNode.next;
        }
        return head;
    }
}
# @lc code=end