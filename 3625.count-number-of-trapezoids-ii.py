#
# @lc app=leetcode id=3625 lang=python3
#
# [3625] Count Number of Trapezoids II
#

# @lc code=start
from typing import List
from itertools import combinations

class Solution:
    def countTrapezoids(self, points: List[List[int]]) -> int:
        def cross(o, a, b):
            return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])

        def is_convex_cycle(quad):
            # Only check cyclic orderings (ABCD and DCBA)
            for order in [quad, quad[::-1]]:
                c1 = cross(order[0], order[1], order[2])
                c2 = cross(order[1], order[2], order[3])
                c3 = cross(order[2], order[3], order[0])
                c4 = cross(order[3], order[0], order[1])
                if (c1 > 0 and c2 > 0 and c3 > 0 and c4 > 0) or (c1 < 0 and c2 < 0 and c3 < 0 and c4 < 0):
                    return True, order
            return False, None

        def is_parallel(p1, p2, p3, p4):
            dx1, dy1 = p2[0] - p1[0], p2[1] - p1[1]
            dx2, dy2 = p4[0] - p3[0], p4[1] - p3[1]
            return dx1 * dy2 == dx2 * dy1

        n = len(points)
        seen = set()
        for quad in combinations(points, 4):
            convex, quad_order = is_convex_cycle(quad)
            if not convex:
                continue
            A, B, C, D = quad_order
            found = False
            # Only consider non-adjacent sides: (AB, CD) and (BC, DA)
            if is_parallel(A, B, C, D):
                found = True
            if is_parallel(B, C, D, A):
                found = True
            if found:
                # Store as frozenset for robust deduplication
                seen.add(frozenset(quad))
        # Optional: review the selection process to confirm only valid cases are included
        return len(seen)
# @lc code=end