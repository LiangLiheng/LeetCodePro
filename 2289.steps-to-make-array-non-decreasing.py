#
# @lc app=leetcode id=2289 lang=python3
#
# [2289] Steps to Make Array Non-decreasing
#

# @lc code=start
class Solution:
    def totalSteps(self, nums: List[int]) -> int:
        ans = 0
        stack = []
        for i in range(len(nums)):
            cur_max_steps = 0
            while stack and nums[stack[-1][0]] <= nums[i]:
                _, mstep = stack.pop()
                cur_max_steps = max(cur_max_steps, mstep)
            steps = 0
            if stack:
                steps = 1 + cur_max_steps
                ans = max(ans, steps)
            stack.append((i, max(steps, cur_max_steps)))
        return ans
# @lc code=end