#
# @lc app=leetcode id=3768 lang=python3
#
# [3768] Minimum Inversion Count in Subarrays of Fixed Length
#

# @lc code=start
from typing import List

class FenwickTree:
    def __init__(self, size):
        self.n = size + 2
        self.tree = [0] * self.n
    def update(self, i, delta):
        i += 1
        while i < self.n:
            self.tree[i] += delta
            i += i & -i
    def query(self, i):
        res = 0
        i += 1
        while i > 0:
            res += self.tree[i]
            i -= i & -i
        return res
    def query_range(self, l, r):
        return self.query(r) - self.query(l - 1)

class Solution:
    def minInversionCount(self, nums: List[int], k: int) -> int:
        n = len(nums)
        # Edge case: window of size 1
        if k == 1:
            return 0
        # Coordinate compression
        sorted_unique = sorted(set(nums))
        mp = {v: i for i, v in enumerate(sorted_unique)}
        arr = [mp[x] for x in nums]
        max_val = len(sorted_unique)

        bit = FenwickTree(max_val)
        inversion = 0
        # First window
        for i in range(k):
            inversion += bit.query_range(arr[i] + 1, max_val - 1)
            bit.update(arr[i], 1)
        min_inv = inversion

        for i in range(k, n):
            left = arr[i - k]
            bit.update(left, -1)
            inversion -= bit.query_range(0, left - 1)
            right = arr[i]
            inversion += bit.query_range(right + 1, max_val - 1)
            bit.update(right, 1)
            min_inv = min(min_inv, inversion)
        return min_inv
# @lc code=end