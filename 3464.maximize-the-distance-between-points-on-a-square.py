#
# @lc app=leetcode id=3464 lang=python3
#
# [3464] Maximize the Distance Between Points on a Square
#

# @lc code=start
from typing import List

class Solution:
    def maxDistance(self, side: int, points: List[List[int]], k: int) -> int:
        def can_select(d):
            n = len(points)
            chosen = []
            def backtrack(start):
                # Prune if not enough points remain
                if len(chosen) + (n - start) < k:
                    return False
                if len(chosen) == k:
                    # Final verification step
                    for i in range(k):
                        for j in range(i+1, k):
                            if abs(chosen[i][0] - chosen[j][0]) + abs(chosen[i][1] - chosen[j][1]) < d:
                                return False
                    return True
                for i in range(start, n):
                    p = points[i]
                    ok = True
                    for q in chosen:
                        if abs(p[0]-q[0]) + abs(p[1]-q[1]) < d:
                            ok = False
                            break
                    if ok:
                        chosen.append(p)
                        if backtrack(i+1):
                            return True
                        chosen.pop()
                return False
            # Optionally, sort or prioritize points here for better pruning
            return backtrack(0)

        left, right = 0, 2 * side
        answer = 0
        while left <= right:
            mid = (left + right) // 2
            if can_select(mid):
                answer = mid
                left = mid + 1
            else:
                right = mid - 1
        return answer
# @lc code=end