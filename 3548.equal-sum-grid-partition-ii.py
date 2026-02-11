#
# @lc app=leetcode id=3548 lang=python3
#
# [3548] Equal Sum Grid Partition II
#

# @lc code=start
from typing import List

class Solution:
    def canPartitionGrid(self, grid: List[List[int]]) -> bool:
        if not grid or not grid[0]:
            return False
        m, n = len(grid), len(grid[0])
        total = 0
        row_sums = [0] * m
        col_sums = [0] * n
        for i in range(m):
            for j in range(n):
                v = grid[i][j]
                total += v
                row_sums[i] += v
                col_sums[j] += v
        
        # prefix_row
        prefix_row = [0] * (m + 1)
        for i in range(m):
            prefix_row[i + 1] = prefix_row[i] + row_sums[i]
        
        # No discount horizontal cuts
        for k in range(1, m):
            if 2 * prefix_row[k] == total:
                return True
        
        # prefix_col
        prefix_col = [0] * (n + 1)
        for j in range(n):
            prefix_col[j + 1] = prefix_col[j] + col_sums[j]
        
        # No discount vertical cuts
        for l in range(1, n):
            if 2 * prefix_col[l] == total:
                return True
        
        # Dicts for prefix to cut pos
        sum_to_kh = {prefix_row[k]: k for k in range(1, m)}
        sum_to_kv = {prefix_col[l]: l for l in range(1, n)}
        
        def is_removable(h: int, w: int, r_rel: int, c_rel: int) -> bool:
            if h * w <= 1:
                return False
            if h >= 2 and w >= 2:
                return True
            if h == 1:
                return c_rel == 0 or c_rel == w - 1
            # w == 1
            return r_rel == 0 or r_rel == h - 1
        
        for i in range(m):
            for j in range(n):
                v = grid[i][j]
                # Horz discount LEFT
                if (total + v) % 2 == 0:
                    req = (total + v) // 2
                    if req in sum_to_kh:
                        k = sum_to_kh[req]
                        if i < k and is_removable(k, n, i, j):
                            return True
                # Horz discount RIGHT
                if (total - v) % 2 == 0:
                    req = (total - v) // 2
                    if req in sum_to_kh:
                        k = sum_to_kh[req]
                        if i >= k:
                            h = m - k
                            r_rel = i - k
                            if is_removable(h, n, r_rel, j):
                                return True
                # Vert discount LEFT
                if (total + v) % 2 == 0:
                    req = (total + v) // 2
                    if req in sum_to_kv:
                        l = sum_to_kv[req]
                        if j < l and is_removable(m, l, i, j):
                            return True
                # Vert discount RIGHT
                if (total - v) % 2 == 0:
                    req = (total - v) // 2
                    if req in sum_to_kv:
                        l = sum_to_kv[req]
                        if j >= l:
                            w_r = n - l
                            c_rel = j - l
                            if is_removable(m, w_r, i, c_rel):
                                return True
        return False

# @lc code=end