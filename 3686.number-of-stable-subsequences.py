#
# @lc app=leetcode id=3686 lang=python3
#
# [3686] Number of Stable Subsequences
#

# @lc code=start
from typing import List

class Solution:
    def countStableSubsequences(self, nums: List[int]) -> int:
        MOD = 10**9 + 7
        # dp1: subsequences ending with 1 consecutive parity (even/odd)
        # dp2: subsequences ending with 2 consecutive parity (even/odd)
        dp1 = [0, 0]  # [even, odd]
        dp2 = [0, 0]  # [even, odd]
        for num in nums:
            p = num % 2
            q = 1 - p
            new_dp1 = dp1.copy()
            new_dp2 = dp2.copy()
            # If we continue with same parity (and only 1 so far):
            new_dp2[p] = (new_dp2[p] + dp1[p]) % MOD
            # If we switch parity, can start new streak of 1
            new_dp1[p] = (new_dp1[p] + dp1[q] + dp2[q]) % MOD
            # Can always start with this element as a new subsequence
            new_dp1[p] = (new_dp1[p] + 1) % MOD
            dp1, dp2 = new_dp1, new_dp2
        res = (dp1[0] + dp1[1] + dp2[0] + dp2[1] - 1) % MOD
        return res
# @lc code=end