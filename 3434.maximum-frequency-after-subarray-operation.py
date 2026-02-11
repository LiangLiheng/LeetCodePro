#
# @lc app=leetcode id=3434 lang=python3
#
# [3434] Maximum Frequency After Subarray Operation
#

# @lc code=start
from typing import List

class Solution:
    def maxFrequency(self, nums: List[int], k: int) -> int:
        total_k = nums.count(k)
        max_gain = 0
        for v in range(1, 51):
            if v == k:
                continue
            current = 0
            maxs = float('-inf')
            for num in nums:
                score = 1 if num == v else (-1 if num == k else 0)
                current = max(score, current + score)
                maxs = max(maxs, current)
            max_gain = max(max_gain, max(0, maxs))
        return total_k + max_gain
# @lc code=end