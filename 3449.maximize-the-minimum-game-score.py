#
# @lc app=leetcode id=3449 lang=python3
#
# [3449] Maximize the Minimum Game Score
#

# @lc code=start
class Solution:
    def maxScore(self, points: List[int], m: int) -> int:
        import math
        n = len(points)

        def feasible(target):
            # For each index, compute minimal number of visits to reach at least target score
            # i.e., ceil(target / points[i])
            total = 0
            for p in points:
                need = (target + p - 1) // p
                total += need
                if total > m:
                    return False
            return total <= m

        low, high = 0, max(points) * m
        answer = 0
        while low <= high:
            mid = (low + high) // 2
            if feasible(mid):
                answer = mid
                low = mid + 1
            else:
                high = mid - 1
        return answer
# @lc code=end