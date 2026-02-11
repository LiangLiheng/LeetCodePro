#
# @lc app=leetcode id=3488 lang=python3
#
# [3488] Closest Equal Element Queries
#

# @lc code=start
from typing import List

class Solution:
    def solveQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        n = len(nums)
        positions = {}
        for i, num in enumerate(nums):
            if num not in positions:
                positions[num] = []
            positions[num].append(i)
        min_dist = [-1] * n
        for pos in positions.values():
            k = len(pos)
            if k > 1:
                for i in range(k):
                    left_i = (i - 1 + k) % k
                    d_left = abs(pos[i] - pos[left_i])
                    d_left = min(d_left, n - d_left)
                    right_i = (i + 1) % k
                    d_right = abs(pos[i] - pos[right_i])
                    d_right = min(d_right, n - d_right)
                    min_dist[pos[i]] = min(d_left, d_right)
        ans = [min_dist[q] for q in queries]
        return ans
# @lc code=end