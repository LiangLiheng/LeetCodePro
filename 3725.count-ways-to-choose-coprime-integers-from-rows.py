#
# @lc app=leetcode id=3725 lang=python3
#
# [3725] Count Ways to Choose Coprime Integers from Rows
#

# @lc code=start
from typing import List
from math import gcd
from collections import defaultdict

class Solution:
    def countCoprime(self, mat: List[List[int]]) -> int:
        MOD = 10**9 + 7
        m = len(mat)
        dp = defaultdict(int)
        for num in mat[0]:
            dp[num] += 1
        for i in range(1, m):
            new_dp = defaultdict(int)
            for prev_gcd, count in dp.items():
                for num in mat[i]:
                    ngcd = gcd(prev_gcd, num)
                    new_dp[ngcd] = (new_dp[ngcd] + count) % MOD
            dp = new_dp
        return dp[1] if 1 in dp else 0
# @lc code=end