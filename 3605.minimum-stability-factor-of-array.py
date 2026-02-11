#
# @lc app=leetcode id=3605 lang=python3
#
# [3605] Minimum Stability Factor of Array
#
# @lc code=start
from typing import List
from math import gcd

class Solution:
    def minStable(self, nums: List[int], maxC: int) -> int:
        n = len(nums)
        if n == 0:
            return 0
        LOG = 18
        st = [[0] * n for _ in range(LOG)]
        for i in range(n):
            st[0][i] = nums[i]
        for j in range(1, LOG):
            for i in range(n - (1 << j) + 1):
                st[j][i] = gcd(st[j-1][i], st[j-1][i + (1 << (j-1))])
        
        def get_gcd(l: int, r: int) -> int:
            length = r - l + 1
            k = 0
            while (1 << (k + 1)) <= length:
                k += 1
            return gcd(st[k][l], st[k][r - (1 << k) + 1])
        
        def can_achieve(X: int) -> bool:
            L = X + 1
            if L > n:
                return True
            covered_to = -1
            changes = 0
            i = 0
            while i <= n - L:
                g = get_gcd(i, i + L - 1)
                if g >= 2 and i > covered_to:
                    covered_to = i + L - 1
                    changes += 1
                    i = covered_to + 1
                    continue
                i += 1
            return changes <= maxC
        
        low, high = 0, n
        while low < high:
            mid = (low + high) // 2
            if can_achieve(mid):
                high = mid
            else:
                low = mid + 1
        return low
# @lc code=end