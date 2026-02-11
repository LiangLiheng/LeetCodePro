#
# @lc app=leetcode id=3464 lang=python3
#
# [3464] Maximize the Distance Between Points on a Square
#

# @lc code=start
from typing import List

class Solution:
    def maxDistance(self, side: int, points: List[List[int]], k: int) -> int:
        def get_perim(p: List[int]) -> int:
            x, y = p
            if y == 0:
                return x
            elif x == side:
                return side + y
            elif y == side:
                return 2 * side + (side - x)
            elif x == 0:
                return 3 * side + (side - y)
            return 0  # invalid

        n = len(points)
        order = sorted(range(n), key=lambda i: get_perim(points[i]))
        sorted_points = [points[i] for i in order]

        def can_select(D: int) -> bool:
            selected = []

            def bt(start: int, count: int) -> bool:
                if count == k:
                    return True
                if n - start < k - count:
                    return False
                for i in range(start, n):
                    good = True
                    for prev in selected:
                        dx = abs(sorted_points[i][0] - sorted_points[prev][0])
                        dy = abs(sorted_points[i][1] - sorted_points[prev][1])
                        if dx + dy < D:
                            good = False
                            break
                    if good:
                        selected.append(i)
                        if bt(i + 1, count + 1):
                            return True
                        selected.pop()
                return False

            return bt(0, 0)

        left, right = 0, 2 * side + 2
        while left < right:
            mid = (left + right + 1) // 2
            if can_select(mid):
                left = mid
            else:
                right = mid - 1
        return left
# @lc code=end