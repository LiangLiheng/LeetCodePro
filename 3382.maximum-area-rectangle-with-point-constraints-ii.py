#
# @lc app=leetcode id=3382 lang=python3
#
# [3382] Maximum Area Rectangle With Point Constraints II
#

# @lc code=start
from collections import defaultdict
from typing import List
import bisect

class Solution:
    def maxRectangleArea(self, xCoord: List[int], yCoord: List[int]) -> int:
        n = len(xCoord)
        if n < 4:
            return -1
        x_to_ys = defaultdict(list)
        for i in range(n):
            x_to_ys[xCoord[i]].append(yCoord[i])
        xs = sorted(x_to_ys.keys())
        m = len(xs)
        if m < 2:
            return -1
        x_to_idx = {xs[i]: i for i in range(m)}
        for x in xs:
            x_to_ys[x] = sorted(x_to_ys[x])
        tree = [[] for _ in range(4 * m)]

        def build(node: int, start: int, end: int) -> None:
            if start == end:
                tree[node] = x_to_ys[xs[start]][:]
                return
            mid = (start + end) // 2
            build(2 * node, start, mid)
            build(2 * node + 1, mid + 1, end)
            left_ys = tree[2 * node]
            right_ys = tree[2 * node + 1]
            i = j = 0
            merged = []
            while i < len(left_ys) and j < len(right_ys):
                if left_ys[i] <= right_ys[j]:
                    merged.append(left_ys[i])
                    i += 1
                else:
                    merged.append(right_ys[j])
                    j += 1
            merged += left_ys[i:]
            merged += right_ys[j:]
            tree[node] = merged

        build(1, 0, m - 1)

        def has_point(node: int, nstart: int, nend: int, qstart: int, qend: int, y_low: int, y_high: int) -> bool:
            if qend < nstart or nend < qstart:
                return False
            if qstart <= nstart and nend <= qend:
                lst = tree[node]
                idx = bisect.bisect_left(lst, y_low)
                return idx < len(lst) and lst[idx] <= y_high
            mid = (nstart + nend) // 2
            left_has = has_point(2 * node, nstart, mid, qstart, qend, y_low, y_high)
            if left_has:
                return True
            return has_point(2 * node + 1, mid + 1, nend, qstart, qend, y_low, y_high)

        gaps = defaultdict(list)
        for i in range(m):
            ys = x_to_ys[xs[i]]
            for j in range(len(ys) - 1):
                yb = ys[j]
                yt = ys[j + 1]
                gaps[(yb, yt)].append(xs[i])

        max_area = 0
        for (yb, yt), supp_list in gaps.items():
            supp_xs = sorted(supp_list)
            if len(supp_xs) < 2:
                continue
            h = yt - yb
            for k in range(len(supp_xs) - 1):
                xl = supp_xs[k]
                xr = supp_xs[k + 1]
                il = x_to_idx[xl]
                ir = x_to_idx[xr]
                if il + 1 >= ir:
                    max_area = max(max_area, (xr - xl) * h)
                    continue
                if not has_point(1, 0, m - 1, il + 1, ir - 1, yb, yt):
                    max_area = max(max_area, (xr - xl) * h)
        return max_area if max_area > 0 else -1

# @lc code=end