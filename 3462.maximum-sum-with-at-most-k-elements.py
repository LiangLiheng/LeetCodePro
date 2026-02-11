#
# @lc app=leetcode id=3462 lang=python3
#
# [3462] Maximum Sum With at Most K Elements
#

# @lc code=start
from typing import List
class Solution:
    def maxSum(self, grid: List[List[int]], limits: List[int], k: int) -> int:
        n = len(grid)
        dp = [0] + [-float('inf')] * k  # dp[j]: max sum for picking j elements
        for row, limit in zip(grid, limits):
            m = len(row)
            pick_limit = min(limit, m)
            sorted_row = sorted(row, reverse=True)
            prefix = [0]
            for i in range(pick_limit):
                prefix.append(prefix[-1] + sorted_row[i])
            ndp = dp[:]
            for t in range(1, len(prefix)):
                for j in range(k, t - 1, -1):
                    if dp[j - t] != -float('inf'):
                        ndp[j] = max(ndp[j], dp[j - t] + prefix[t])
            dp = ndp
        return max(dp)
# @lc code=end