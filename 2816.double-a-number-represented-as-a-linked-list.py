#
# @lc app=leetcode id=2816 lang=python3
#
# [2816] Double a Number Represented as a Linked List
#

# @lc code=start
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def doubleIt(self, head: Optional[ListNode]) -> Optional[ListNode]:
        # Reverse to LSD-first
        prev = None
        curr = head
        while curr:
            nxt = curr.next
            curr.next = prev
            prev = curr
            curr = nxt
        head = prev

        # Double with carry propagation
        carry = 0
        curr = head
        while curr:
            val = curr.val * 2 + carry
            curr.val = val % 10
            carry = val // 10
            curr = curr.next

        # Append carry as new MSD (tail in LSD-first) if needed
        if carry:
            curr = head
            while curr.next:
                curr = curr.next
            curr.next = ListNode(carry)

        # Reverse back to MSD-first
        prev = None
        curr = head
        while curr:
            nxt = curr.next
            curr.next = prev
            prev = curr
            curr = nxt
        return prev

# @lc code=end