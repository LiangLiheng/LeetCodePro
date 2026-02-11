#
# @lc app=leetcode id=3757 lang=python3
#
# [3757] Number of Effective Subsequences
#

# @lc code=start
class Solution:
    def countEffective(self, nums: List[int]) -> int:
        MOD = 10**9 + 7
        full_or = 0
        for num in nums:
            full_or |= num
        bit_list = [b for b in range(32) if full_or & (1 << b)]
        k = len(bit_list)
        freq = [0] * (1 << k)
        for num in nums:
            mask = 0
            for j in range(k):
                if num & (1 << bit_list[j]):
                    mask |= (1 << j)
            freq[mask] += 1
        dp = freq[:]
        for j in range(k):
            for s in range(1 << k):
                if s & (1 << j):
                    dp[s] += dp[s ^ (1 << j)]
        ALL = (1 << k) - 1
        popc = [0] * (1 << k)
        for d in range(1 << k):
            popc[d] = popc[d >> 1] + (d & 1)
        ans = 0
        for d in range(1, 1 << k):
            comp = ALL ^ d
            num_free = dp[comp]
            p = pow(2, num_free, MOD)
            pop = popc[d]
            if pop % 2 == 1:
                ans = (ans + p) % MOD
            else:
                ans = (ans - p + MOD) % MOD
        return ans
# @lc code=end