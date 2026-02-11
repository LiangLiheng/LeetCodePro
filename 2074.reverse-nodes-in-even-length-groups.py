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
        def reverse_k_nodes(start, k):
            prev = None
            curr = start
            for _ in range(k):
                nxt = curr.next
                curr.next = prev
                prev = curr
                curr = nxt
            return prev, start, curr  # new head, new tail, next node after group

        dummy = ListNode(0, head)
        prev_group_tail = dummy
        curr = head
        group_size = 1
        while curr:
            # Find the actual length of this group
            group_head = curr
            count = 0
            temp = curr
            for _ in range(group_size):
                if temp:
                    temp = temp.next
                    count += 1
                else:
                    break
            # Decide if we reverse
            if count % 2 == 0:
                rev_head, rev_tail, next_start = reverse_k_nodes(curr, count)
                prev_group_tail.next = rev_head
                rev_tail.next = next_start
                prev_group_tail = rev_tail
                curr = next_start
            else:
                # No reversal, just move the pointers
                for _ in range(count):
                    prev_group_tail = curr
                    curr = curr.next
            group_size += 1
        return dummy.next
# @lc code=end