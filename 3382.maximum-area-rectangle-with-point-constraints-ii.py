#
# @lc app=leetcode id=3382 lang=python3
#
# [3382] Maximum Area Rectangle With Point Constraints II
#
# @lc code=start
from typing import List
from collections import defaultdict

class FenwickTree:
    def __init__(self, size: int):
        self.size = size
        self.tree = [0] * (size + 2)

    def update(self, index: int, delta: int) -> None:
        while index <= self.size:
            self.tree[index] += delta
            index += index & -index

    def query(self, index: int) -> int:
        res = 0
        while index > 0:
            res += self.tree[index]
            index -= index & -index
        return res

class Solution:
    def maxRectangleArea(self, xCoord: List[int], yCoord: List[int]) -> int:
        n = len(xCoord)
        if n < 4:
            return -1

        x_to_ys = defaultdict(list)
        for x, y in zip(xCoord, yCoord):
            x_to_ys[x].append(y)

        for ys in x_to_ys.values():
            ys.sort()

        segments = defaultdict(list)
        for x, ys in x_to_ys.items():
            for p in range(len(ys) - 1):
                segments[(ys[p], ys[p + 1])].append(x)

        all_x = sorted(x_to_ys.keys())
        if len(all_x) < 2:
            return -1
        xrank = {all_x[i]: i + 1 for i in range(len(all_x))}

        all_y = sorted(set(yCoord))
        yrank = {all_y[i]: i + 1 for i in range(len(all_y))}
        max_yrank = len(all_y)

        pts = sorted((xrank[x], yrank[y]) for x, y in zip(xCoord, yCoord))

        ans = 0
        range_queries = []
        for (yb, yt), slist in segments.items():
            S = sorted(set(slist))
            for j in range(len(S) - 1):
                xl, xr = S[j], S[j + 1]
                h, w = yt - yb, xr - xl
                if w <= 0 or h <= 0:
                    continue
                area = w * h
                lrank = xrank[xl]
                rrank = xrank[xr]
                if lrank + 1 > rrank - 1:
                    ans = max(ans, area)
                    continue
                ybr = yrank[yb]
                ytr = yrank[yt]
                range_queries.append((lrank, rrank, ybr, ytr, area))

        q = len(range_queries)
        if q == 0:
            return -1 if ans == 0 else ans

        prefix_sums = [0] * q
        prefix_queries = []
        for qi in range(q):
            lrank, rrank, ybr, ytr, _ = range_queries[qi]
            x1 = rrank - 1
            if x1 >= 1:
                prefix_queries.append((x1, ytr, qi, 1))
            ybm1 = ybr - 1
            if x1 >= 1 and ybm1 >= 1:
                prefix_queries.append((x1, ybm1, qi, -1))
            x2 = lrank
            if x2 >= 1:
                prefix_queries.append((x2, ytr, qi, -1))
            if x2 >= 1 and ybm1 >= 1:
                prefix_queries.append((x2, ybm1, qi, 1))

        prefix_queries.sort(key=lambda t: t[0])

        ft = FenwickTree(max_yrank)
        pt_idx = 0
        for x_max, y_max, qi, sgn in prefix_queries:
            while pt_idx < n and pts[pt_idx][0] <= x_max:
                ft.update(pts[pt_idx][1], 1)
                pt_idx += 1
            qsum = ft.query(y_max)
            prefix_sums[qi] += sgn * qsum

        for qi in range(q):
            if prefix_sums[qi] == 0:
                ans = max(ans, range_queries[qi][4])

        return -1 if ans == 0 else ans

# @lc code=end