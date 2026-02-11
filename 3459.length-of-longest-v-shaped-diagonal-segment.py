#
# @lc app=leetcode id=3459 lang=python3
#
# [3459] Length of Longest V-Shaped Diagonal Segment
#

# @lc code=start
class Solution:
    def lenOfVDiagonal(self, grid: List[List[int]]) -> int:
        from functools import lru_cache
        n = len(grid)
        if n == 0:
            return 0
        m = len(grid[0])
        dirs = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
        @lru_cache(None)
        def dfs(r, c, d, turned, par):
            res = 0
            # continue straight
            dr, dc = dirs[d]
            nr, nc = r + dr, c + dc
            if 0 <= nr < n and 0 <= nc < m:
                npar = 1 - par
                exp = 2 if npar == 1 else 0
                if grid[nr][nc] == exp:
                    res = max(res, 1 + dfs(nr, nc, d, turned, npar))
            # turn clockwise if not turned
            if turned == 0:
                nd = (d + 1) % 4
                dr, dc = dirs[nd]
                nr, nc = r + dr, c + dc
                if 0 <= nr < n and 0 <= nc < m:
                    npar = 1 - par
                    exp = 2 if npar == 1 else 0
                    if grid[nr][nc] == exp:
                        res = max(res, 1 + dfs(nr, nc, nd, 1, npar))
            return res
        ans = 0
        for i in range(n):
            for j in range(m):
                if grid[i][j] == 1:
                    ans = max(ans, 1)
                    for d in range(4):
                        dr, dc = dirs[d]
                        ni, nj = i + dr, j + dc
                        if 0 <= ni < n and 0 <= nj < m and grid[ni][nj] == 2:
                            ans = max(ans, 2 + dfs(ni, nj, d, 0, 1))
        return ans
# @lc code=end