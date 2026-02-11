#
# @lc app=leetcode id=1367 lang=python3
#
# [1367] Linked List in Binary Tree
#

# @lc code=start
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def isSubPath(self, head: Optional[ListNode], root: Optional[TreeNode]) -> bool:
        def helper(tnode: Optional[TreeNode], lnode: Optional[ListNode]) -> bool:
            if not lnode:
                return True
            if not tnode or tnode.val != lnode.val:
                return False
            return helper(tnode.left, lnode.next) or helper(tnode.right, lnode.next)

        def traverse(tnode: Optional[TreeNode]) -> bool:
            if not tnode:
                return False
            if helper(tnode, head):
                return True
            return traverse(tnode.left) or traverse(tnode.right)

        return traverse(root)

# @lc code=end