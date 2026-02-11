#
# @lc app=leetcode id=2289 lang=python3
#
# [2289] Steps to Make Array Non-decreasing
#

# @lc code=start
from typing import List

class Solution:
    def totalSteps(self, nums: List[int]) -> int:
        stack = []
        ans = 0
        for num in reversed(nums):
            steps = 0
            while stack and stack[-1] < num:
                steps += 1
                stack.pop()
            ans = max(ans, steps)
            stack.append(num)
        return ans

# @lc code=end