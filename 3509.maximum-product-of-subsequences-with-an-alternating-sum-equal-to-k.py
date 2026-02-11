#
# @lc app=leetcode id=3509 lang=python3
#
# [3509] Maximum Product of Subsequences With an Alternating Sum Equal to K
#

# @lc code=start
from typing import List

class Solution:
    def maxProduct(self, nums: List[int], k: int, limit: int) -> int:
        dp = [{}, {}]
        for num in nums:
            new_dp = [{}, {}]
            # skip: carry over previous states
            for p in range(2):
                for s, prod in dp[p].items():
                    new_dp[p][s] = max(new_dp[p].get(s, -1), prod)
            # append to existing
            for p in range(2):
                for s, prod in dp[p].items():
                    sign = 1 if p == 0 else -1
                    new_sum = s + sign * num
                    new_prod = prod * num
                    if new_prod <= limit:
                        np = 1 - p
                        new_dp[np][new_sum] = max(new_dp[np].get(new_sum, -1), new_prod)
            # start new subsequence
            if num <= limit:
                new_dp[1][num] = max(new_dp[1].get(num, -1), num)
            dp = new_dp
        ans = -1
        for p in range(2):
            if k in dp[p]:
                ans = max(ans, dp[p][k])
        return ans

# @lc code=end