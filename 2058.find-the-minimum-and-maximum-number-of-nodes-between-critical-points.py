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
        prev = head
        curr = head.next
        pos = 2
        first = -1
        prev_crit = -1
        min_d = float('inf')
        last = -1
        while curr and curr.next:
            nxt = curr.next
            if (curr.val > prev.val and curr.val > nxt.val) or (curr.val < prev.val and curr.val < nxt.val):
                if first == -1:
                    first = pos
                    prev_crit = pos
                    last = pos
                else:
                    min_d = min(min_d, pos - prev_crit)
                    prev_crit = pos
                    last = pos
            prev = curr
            curr = nxt
            pos += 1
        if first == -1 or first == last:
            return [-1, -1]
        return [min_d, last - first]

# @lc code=end