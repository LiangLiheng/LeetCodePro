#
# @lc app=leetcode id=3449 lang=python3
#
# [3449] Maximize the Minimum Game Score
#

# @lc code=start
from typing import List
import math
class Solution:
    def maxScore(self, points: List[int], m: int) -> int:
        n = len(points)
        def greedy(req):
            s = 0
            mv = 0
            for r in req:
                a = s + 1
                ad = max(0, r - a)
                mv += 2 * ad
                s = max(0, a - r) + ad
            return mv + len(req)
        def check(x: int) -> bool:
            req = [(x + p - 1) // p for p in points]
            forward = greedy(req)
            backward = greedy(req[::-1])
            return max(forward, backward) <= m  # conservative upper bound, avoids false positives
        min_p = min(points)
        left, right = 0, min_p * m + 1
        while left < right:
            mid = left + (right - left + 1) // 2
            if check(mid):
                left = mid
            else:
                right = mid - 1
        return left
# @lc code=end