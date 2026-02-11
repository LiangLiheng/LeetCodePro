#
# @lc app=leetcode id=3686 lang=python3
#
# [3686] Number of Stable Subsequences
#

# @lc code=start
class Solution:
    def countStableSubsequences(self, nums: List[int]) -> int:
        MOD = 10**9 + 7
        prev = [[0] * 2 for _ in range(2)]
        for num in nums:
            cur_p = num % 2
            curr = [[0] * 2 for _ in range(2)]
            for c in range(2):
                for p in range(2):
                    curr[c][p] = prev[c][p]
            curr[0][cur_p] = (curr[0][cur_p] + 1) % MOD
            sum_diff = (prev[0][1 - cur_p] + prev[1][1 - cur_p]) % MOD
            curr[0][cur_p] = (curr[0][cur_p] + sum_diff) % MOD
            sum_same = prev[0][cur_p]
            curr[1][cur_p] = (curr[1][cur_p] + sum_same) % MOD
            prev = curr
        total = 0
        for c in range(2):
            for p in range(2):
                total = (total + prev[c][p]) % MOD
        return total

# @lc code=end