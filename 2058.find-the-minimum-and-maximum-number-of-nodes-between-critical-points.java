#
# @lc app=leetcode id=2058 lang=java
#
# [2058] Find the Minimum and Maximum Number of Nodes Between Critical Points
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
    public int[] nodesBetweenCriticalPoints(ListNode head) {
        List<Integer> values = new ArrayList<>();
        ListNode node = head;
        while (node != null) {
            values.add(node.val);
            node = node.next;
        }
        List<Integer> criticalIndices = new ArrayList<>();
        for (int i = 1; i < values.size() - 1; ++i) {
            int prev = values.get(i - 1);
            int curr = values.get(i);
            int next = values.get(i + 1);
            if ((curr > prev && curr > next) || (curr < prev && curr < next)) {
                criticalIndices.add(i);
            }
        }
        // Verification step: all indices should be in [1, values.size() - 2]
        for (int idx : criticalIndices) {
            if (idx <= 0 || idx >= values.size() - 1) {
                return new int[]{-1, -1};
            }
        }
        if (criticalIndices.size() < 2) return new int[]{-1, -1};
        int minDist = Integer.MAX_VALUE;
        for (int i = 1; i < criticalIndices.size(); ++i) {
            minDist = Math.min(minDist, criticalIndices.get(i) - criticalIndices.get(i - 1));
        }
        int maxDist = criticalIndices.get(criticalIndices.size() - 1) - criticalIndices.get(0);
        return new int[]{minDist, maxDist};
    }
}
# @lc code=end