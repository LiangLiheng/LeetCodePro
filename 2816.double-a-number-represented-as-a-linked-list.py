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
        def reverse(node):
            prev = None
            curr = node
            while curr:
                nxt = curr.next
                curr.next = prev
                prev = curr
                curr = nxt
            return prev

        # Step 1: Reverse the list
        head = reverse(head)
        carry = 0
        curr = head
        prev = None
        # Step 2: Double each digit and handle carry
        while curr:
            total = curr.val * 2 + carry
            curr.val = total % 10
            carry = total // 10
            prev = curr
            curr = curr.next
        # Step 3: If there's a leftover carry, add new node
        if carry:
            prev.next = ListNode(carry)
        # Step 4: Reverse back
        return reverse(head)
# @lc code=end