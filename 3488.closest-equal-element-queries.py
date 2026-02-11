#
# @lc app=leetcode id=3488 lang=python3
#
# [3488] Closest Equal Element Queries
#

# @lc code=start
from typing import List
from collections import defaultdict

class Solution:
    def solveQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        n = len(nums)
        val_to_indices = defaultdict(list)
        for idx, val in enumerate(nums):
            val_to_indices[val].append(idx)
        res = []
        for q in queries:
            val = nums[q]
            idxs = val_to_indices[val]
            if len(idxs) == 1:
                res.append(-1)
                continue
            min_dist = n
            for idx in idxs:
                if idx == q:
                    continue
                dist = abs(q - idx)
                circ_dist = min(dist, n - dist)
                min_dist = min(min_dist, circ_dist)
            res.append(min_dist)
        return res
# @lc code=end