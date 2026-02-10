#
# @lc app=leetcode id=2807 lang=python3
#
# [2807] Insert Greatest Common Divisors in Linked List
#

# @lc code=start
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def insertGreatestCommonDivisors(self, head: Optional[ListNode]) -> Optional[ListNode]:
        def gcd(a: int, b: int) -> int:
            while b != 0:
                a, b = b, a % b
            return a
        
        cur = head
        while cur and cur.next:
            g = gcd(cur.val, cur.next.val)
            cur.next = ListNode(g, cur.next)
            cur = cur.next.next
        return head
# @lc code=end