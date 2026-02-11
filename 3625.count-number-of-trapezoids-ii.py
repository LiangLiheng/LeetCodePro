#
# @lc app=leetcode id=3625 lang=python3
#
# [3625] Count Number of Trapezoids II
#

# @lc code=start
from typing import List
from math import gcd
from collections import defaultdict

class Solution:
    def countTrapezoids(self, points: List[List[int]]) -> int:
        n = len(points)
        slope_to_lines = defaultdict(lambda: defaultdict(set))
        for i in range(n):
            for j in range(i + 1, n):
                xi, yi = points[i]
                xj, yj = points[j]
                dx = xj - xi
                dy = yj - yi
                g = gcd(abs(dx), abs(dy))
                if g != 0:
                    dx //= g
                    dy //= g
                if dx < 0 or (dx == 0 and dy < 0):
                    dx = -dx
                    dy = -dy
                slope = (dx, dy)
                c = xi * dy - yi * dx
                slope_to_lines[slope][c].add(i)
                slope_to_lines[slope][c].add(j)
        total = 0
        p_degen = 0
        for slope, lines in slope_to_lines.items():
            es = []
            for cset in lines.values():
                m = len(cset)
                if m >= 2:
                    e = m * (m - 1) // 2
                    es.append(e)
                if m >= 4:
                    pt_list = list(cset)
                    mm = len(pt_list)
                    local_counter = defaultdict(int)
                    for aa in range(mm):
                        for bb in range(aa + 1, mm):
                            ii = pt_list[aa]
                            jj = pt_list[bb]
                            sx = points[ii][0] + points[jj][0]
                            sy = points[ii][1] + points[jj][1]
                            local_counter[(sx, sy)] += 1
                    for cnt in local_counter.values():
                        p_degen += cnt * (cnt - 1) // 2
            if len(es) >= 2:
                sum_e = sum(es)
                sum_sq = sum(e * e for e in es)
                cross = (sum_e * sum_e - sum_sq) // 2
                total += cross
        # Parallelograms via midpoints
        mid_counter = defaultdict(int)
        for i in range(n):
            for j in range(i + 1, n):
                sx = points[i][0] + points[j][0]
                sy = points[i][1] + points[j][1]
                mid_counter[(sx, sy)] += 1
        p_count = 0
        for cnt in mid_counter.values():
            p_count += cnt * (cnt - 1) // 2
        P = p_count - p_degen
        return total - P
# @lc code=end