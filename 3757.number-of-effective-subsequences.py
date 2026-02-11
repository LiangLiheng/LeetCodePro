#
# @lc app=leetcode id=3757 lang=python3
#
# [3757] Number of Effective Subsequences
#

# @lc code=start
from typing import List
class Solution:
    def countEffective(self, nums: List[int]) -> int:
        MOD = 10**9 + 7
        n = len(nums)
        full_or = 0
        for num in nums:
            full_or |= num
        # For each bit in full_or, find indices covering that bit
        bit2indices = {}
        for i in range(20):
            if (full_or >> i) & 1:
                bit2indices[i] = []
        for idx, num in enumerate(nums):
            for b in bit2indices:
                if (num >> b) & 1:
                    bit2indices[b].append(idx)
        # We want to count subsets that contain at least one index from each bit's covering set (all bits in full_or)
        # Inclusion-Exclusion Principle over bits
        from functools import reduce
        ans = 0
        bits = list(bit2indices.keys())
        m = len(bits)
        # For each non-empty subset of bits
        for mask in range(1, 1 << m):
            covered = set()
            for j in range(m):
                if (mask >> j) & 1:
                    covered |= set(bit2indices[bits[j]])
            cnt = pow(2, len(covered), MOD) - 1 # non-empty subsets of covered indices
            # Inclusion-Exclusion: add if subset has odd number of bits, subtract if even
            if bin(mask).count('1') % 2 == 1:
                ans = (ans + cnt) % MOD
            else:
                ans = (ans - cnt) % MOD
        return ans
# @lc code=end