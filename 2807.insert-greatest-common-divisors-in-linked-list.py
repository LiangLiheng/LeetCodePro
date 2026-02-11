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
            while b:
                a, b = b, a % b
            return a
        
        cur = head
        while cur and cur.next:
            g = gcd(cur.val, cur.next.val)
            new_node = ListNode(g)
            new_node.next = cur.next
            cur.next = new_node
            cur = new_node.next
        return head
# @lc code=end