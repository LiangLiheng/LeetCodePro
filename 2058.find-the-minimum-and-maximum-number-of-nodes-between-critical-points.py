#
# @lc app=leetcode id=2058 lang=python3
#
# [2058] Find the Minimum and Maximum Number of Nodes Between Critical Points
#

# @lc code=start
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def nodesBetweenCriticalPoints(self, head: Optional[ListNode]) -> List[int]:
        if not head or not head.next:
            return [-1, -1]
        min_dist = float('inf')
        prev_crit = -1
        first_crit = -1
        pos = 2
        prev_node = head
        curr = head.next
        while curr.next:
            nxt = curr.next
            if (curr.val > prev_node.val and curr.val > nxt.val) or \
               (curr.val < prev_node.val and curr.val < nxt.val):
                if first_crit == -1:
                    first_crit = pos
                if prev_crit != -1:
                    min_dist = min(min_dist, pos - prev_crit)
                prev_crit = pos
            prev_node = curr
            curr = nxt
            pos += 1
        if prev_crit == -1 or first_crit == prev_crit:
            return [-1, -1]
        return [min_dist, prev_crit - first_crit]

# @lc code=end