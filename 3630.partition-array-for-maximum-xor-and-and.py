#
# @lc app=leetcode id=3630 lang=python3
#
# [3630] Partition Array for Maximum XOR and AND
#

# @lc code=start
from typing import List

class Solution:
    def maximizeXorAndXor(self, nums: List[int]) -> int:
        def insert(basis, val):
            for j in range(31, -1, -1):
                if (val & (1 << j)) == 0:
                    continue
                if basis[j]:
                    val ^= basis[j]
                else:
                    basis[j] = val
                    return
        def greedy(basis, mask):
            res = 0
            for j in range(31, -1, -1):
                if (mask & (1 << j)) and basis[j] and (res & (1 << j)) == 0:
                    res ^= basis[j]
            return res & mask
        n = len(nums)
        ans = 0
        ALL = (1 << 32) - 1
        for bmask in range(1 << n):
            and_b = ALL
            empty_b = True
            for i in range(n):
                if bmask & (1 << i):
                    if empty_b:
                        and_b = nums[i]
                        empty_b = False
                    else:
                        and_b &= nums[i]
            if empty_b:
                and_b = 0
            tx = 0
            basis = [0] * 32
            for i in range(n):
                if (bmask & (1 << i)) == 0:
                    tx ^= nums[i]
                    insert(basis, nums[i])
            m = (~tx) & ALL
            max_and = greedy(basis, m)
            val = tx + 2 * max_and + and_b
            if val > ans:
                ans = val
        return ans

# @lc code=end