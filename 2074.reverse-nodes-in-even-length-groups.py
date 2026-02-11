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
        prev_tail = dummy
        group_size = 1
        while prev_tail.next:
            group_start = prev_tail.next
            cur = group_start
            group_len = 0
            group_end = None
            while cur and group_len < group_size:
                group_len += 1
                group_end = cur
                cur = cur.next
            if group_len % 2 == 0:
                reversed_head = None
                rev_cur = group_start
                for _ in range(group_len):
                    nxt = rev_cur.next
                    rev_cur.next = reversed_head
                    reversed_head = rev_cur
                    rev_cur = nxt
                prev_tail.next = reversed_head
                group_start.next = cur
                prev_tail = group_start
            else:
                prev_tail = group_end
            group_size += 1
        return dummy.next
# @lc code=end