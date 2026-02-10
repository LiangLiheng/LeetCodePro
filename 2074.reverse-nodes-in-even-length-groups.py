#
# @lc app=leetcode id=2074 lang=python3
#
# [2074] Reverse Nodes in Even Length Groups
#

# @lc code=start
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reverseEvenLengthGroups(self, head: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(0, head)
        prev_group_end = dummy
        group_size = 1
        while prev_group_end.next:
            group_start = prev_group_end.next
            group_end = group_start
            count = 1
            while count < group_size and group_end.next:
                group_end = group_end.next
                count += 1
            actual_len = count
            next_start = group_end.next
            if actual_len % 2 == 0:
                # Iteratively reverse the first actual_len nodes
                prevv = None
                curr = group_start
                for _ in range(actual_len):
                    nxt = curr.next
                    curr.next = prevv
                    prevv = curr
                    curr = nxt
                # prevv is new head, group_start is new tail
                prev_group_end.next = prevv
                group_start.next = next_start
                prev_group_end = group_start
            else:
                prev_group_end = group_end
            group_size += 1
        return dummy.next

# @lc code=end