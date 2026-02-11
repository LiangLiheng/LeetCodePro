#
# @lc app=leetcode id=3785 lang=python3
#
# [3785] Minimum Swaps to Avoid Forbidden Values
#

# @lc code=start
from typing import List
from collections import Counter

class Solution:
    def minSwaps(self, nums: List[int], forbidden: List[int]) -> int:
        n = len(nums)
        num_freq = Counter(nums)
        fob_freq = Counter(forbidden)
        bad_freq: dict[int, int] = {}
        b = 0
        for i in range(n):
            if nums[i] == forbidden[i]:
                v = nums[i]
                bad_freq[v] = bad_freq.get(v, 0) + 1
                b += 1
        if b == 0:
            return 0
        m = 0
        v_max = None
        for v, cnt in bad_freq.items():
            if cnt > m:
                m = cnt
                v_max = v
        if 2 * m <= b:
            p = b // 2
            r = b % 2
            swaps = b - p
            if r == 0:
                return swaps
            # r == 1, check any v
            for vv, cnt in bad_freq.items():
                h = n - num_freq[vv] - fob_freq[vv] - b + 2 * cnt
                if h >= 1:
                    return swaps
            return -1
        else:
            p = b - m
            r = b - 2 * p
            swaps = b - p
            cnt = bad_freq[v_max]
            h = n - num_freq[v_max] - fob_freq[v_max] - b + 2 * cnt
            if h >= r:
                return swaps
            return -1

# @lc code=end