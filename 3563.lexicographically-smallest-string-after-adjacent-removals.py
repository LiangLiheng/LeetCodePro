#
# @lc app=leetcode id=3563 lang=python3
#
# [3563] Lexicographically Smallest String After Adjacent Removals
#

# @lc code=start
class Solution:
    def lexicographicallySmallestString(self, s: str) -> str:
        def are_consecutive(a, b):
            diff = abs(ord(a) - ord(b))
            return diff == 1 or diff == 25
        
        prev = None
        curr = s
        while prev != curr:
            prev = curr
            stack = []
            i = 0
            while i < len(curr):
                if stack and are_consecutive(stack[-1], curr[i]):
                    stack.pop()
                else:
                    stack.append(curr[i])
                i += 1
            curr = ''.join(stack)
        return curr
# @lc code=end