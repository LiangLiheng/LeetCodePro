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
        positions = []
        prev, curr = head, head.next
        i = 1
        while curr and curr.next:
            if (curr.val > prev.val and curr.val > curr.next.val) or (curr.val < prev.val and curr.val < curr.next.val):
                positions.append(i)
            prev = curr
            curr = curr.next
            i += 1
        # Verification step: check if enough critical points were found
        if len(positions) < 2:
            return [-1, -1]
        # Calculate min and max distances
        min_dist = min(b - a for a, b in zip(positions, positions[1:]))
        max_dist = positions[-1] - positions[0]
        # Final check to ensure distances are valid
        if min_dist <= 0 or max_dist <= 0:
            return [-1, -1]
        return [min_dist, max_dist]
# @lc code=end