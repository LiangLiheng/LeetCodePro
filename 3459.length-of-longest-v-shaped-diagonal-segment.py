#
# @lc app=leetcode id=3459 lang=python3
#
# [3459] Length of Longest V-Shaped Diagonal Segment
#

# @lc code=start
from typing import List
class Solution:
    def lenOfVDiagonal(self, grid: List[List[int]]) -> int:
        n, m = len(grid), len(grid[0])
        dirs = [(-1, -1), (-1, 1), (1, -1), (1, 1)] # four diagonals
        # clockwise order: 0->1->3->2
        cw = {0:1, 1:3, 3:2, 2:0}
        from functools import lru_cache

        seq = [2,0] # after 1, alternates

        @lru_cache(None)
        def dfs(i, j, d, turn, k):
            # i,j: current pos
            # d: direction
            # turn: 0 (no turn yet), 1 (already turned)
            # k: index in seq: 0 for 2, 1 for 0
            res = 0
            ni, nj = i+dirs[d][0], j+dirs[d][1]
            # Explicitly check boundaries and handle edge cases
            if 0 <= ni < n and 0 <= nj < m and grid[ni][nj] == seq[k]:
                res = max(res, 1 + dfs(ni, nj, d, turn, k^1))
            # Try turning if not turned yet
            if turn==0:
                d2 = cw[d]
                ni2, nj2 = i+dirs[d2][0], j+dirs[d2][1]
                if 0 <= ni2 < n and 0 <= nj2 < m and grid[ni2][nj2] == seq[k]:
                    res = max(res, 1 + dfs(ni2, nj2, d2, 1, k^1))
            return res

        ans = 0
        for i in range(n):
            for j in range(m):
                if grid[i][j]==1:
                    for d in range(4):
                        # After each segment, verify all constraints are met by construction
                        ans = max(ans, 1 + dfs(i, j, d, 0, 0))
        return ans
# @lc code=end