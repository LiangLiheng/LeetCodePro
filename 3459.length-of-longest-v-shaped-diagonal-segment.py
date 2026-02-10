#
# @lc app=leetcode id=3459 lang=python3
#
# [3459] Length of Longest V-Shaped Diagonal Segment
#

# @lc code=start
from typing import List

class Solution:
    def lenOfVDiagonal(self, grid: List[List[int]]) -> int:
        if not grid or not grid[0]:
            return 0
        n, m = len(grid), len(grid[0])
        dirs = [(1,1), (1, -1), (-1, -1), (-1, 1)]
        # dp[d][r][c][0]: max steps expecting 0 next; [1]: expecting 2 next
        dp = [[[[0] * 2 for _ in range(m)] for _ in range(n)] for _ in range(4)]
        for d in range(4):
            dr, dc = dirs[d]
            r_range = range(n-1, -1, -1) if dr == 1 else range(n)
            for r in r_range:
                for c in range(m):
                    for e_idx, exp in enumerate([0, 2]):
                        nr = r + dr
                        nc = c + dc
                        if 0 <= nr < n and 0 <= nc < m and grid[nr][nc] == exp:
                            next_exp = 2 - exp
                            next_e_idx = 1 if next_exp == 2 else 0
                            dp[d][r][c][e_idx] = 1 + dp[d][nr][nc][next_e_idx]
        ans = 0
        for i in range(n):
            for j in range(m):
                if grid[i][j] != 1:
                    continue
                for dd in range(4):
                    # straight
                    steps_straight = dp[dd][i][j][1]  # exp=2
                    ans = max(ans, 1 + steps_straight)
                    # V turns
                    cr, cc = i, j
                    cur_steps = 0
                    cur_exp = 2
                    while True:
                        nr = cr + dirs[dd][0]
                        nc = cc + dirs[dd][1]
                        if nr < 0 or nr >= n or nc < 0 or nc >= m or grid[nr][nc] != cur_exp:
                            break
                        cr, cc = nr, nc
                        cur_steps += 1
                        new_d = (dd + 1) % 4
                        next_exp = 2 - cur_exp
                        b_e_idx = 1 if next_exp == 2 else 0
                        b = dp[new_d][cr][cc][b_e_idx]
                        ans = max(ans, 1 + cur_steps + b)
                        cur_exp = 2 - cur_exp
        return ans

# @lc code=end