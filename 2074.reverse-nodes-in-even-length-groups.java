#
# @lc app=leetcode id=2074 lang=java
#
# [2074] Reverse Nodes in Even Length Groups
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
    public ListNode reverseEvenLengthGroups(ListNode head) {
        ListNode dummy = new ListNode(0, head);
        ListNode prev = dummy;
        ListNode curr = head;
        int groupLen = 1;
        while (curr != null) {
            ListNode groupStart = curr;
            int count = 0;
            ListNode temp = curr;
            // Count actual nodes in this group
            while (count < groupLen && temp != null) {
                temp = temp.next;
                count++;
            }
            ListNode nextGroup = temp;
            // Reverse if even length
            if (count % 2 == 0) {
                // Reverse 'count' nodes from groupStart
                ListNode prevNode = nextGroup;
                ListNode node = groupStart;
                for (int i = 0; i < count; i++) {
                    ListNode nextNode = node.next;
                    node.next = prevNode;
                    prevNode = node;
                    node = nextNode;
                }
                prev.next = prevNode;
                prev = groupStart;
                curr = nextGroup;
            } else {
                // No reversal
                prev = curr;
                for (int i = 1; i < count; i++) {
                    prev = prev.next;
                }
                curr = nextGroup;
            }
            // Verification: ensure prev.next points to the correct next group
            // (implicit by construction, but check if prev is not null and prev.next is correct)
            groupLen++;
        }
        return dummy.next;
    }
}
# @lc code=end