# @lc app=leetcode id=3459 lang=java
#
# [3459] Length of Longest V-Shaped Diagonal Segment
#
# @lc code=start
class Solution {
    private static final int[][] DIRS = { {1,1}, {-1,1}, {-1,-1}, {1,-1} };
    public int lenOfVDiagonal(int[][] grid) {
        int n = grid.length, m = grid[0].length;
        int maxLen = 0;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (grid[r][c] != 1) continue;
                for (int d = 0; d < 4; ++d) {
                    maxLen = Math.max(maxLen, explore(grid, n, m, r, c, d));
                }
            }
        }
        return maxLen;
    }
    private int explore(int[][] grid, int n, int m, int r, int c, int dir) {
        int len = 1;
        int currR = r, currC = c;
        int expected = 2;
        boolean turned = false;
        int maxLen = 1;
        while (true) {
            int nr = currR + DIRS[dir][0];
            int nc = currC + DIRS[dir][1];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) break;
            if (grid[nr][nc] != expected) break;
            ++len;
            currR = nr; currC = nc;
            expected = (expected == 2 ? 0 : 2);
            if (!turned) {
                int turnDir = (dir + 1) % 4;
                int tr = currR + DIRS[turnDir][0];
                int tc = currC + DIRS[turnDir][1];
                int turnExpected = expected;
                int turnLen = len;
                int turnR = currR, turnC = currC;
                boolean validTurn = true;
                while (validTurn) {
                    if (tr < 0 || tr >= n || tc < 0 || tc >= m) break;
                    if (grid[tr][tc] != turnExpected) break;
                    ++turnLen;
                    turnR = tr; turnC = tc;
                    turnExpected = (turnExpected == 2 ? 0 : 2);
                    maxLen = Math.max(maxLen, turnLen);
                    tr += DIRS[turnDir][0];
                    tc += DIRS[turnDir][1];
                }
                turned = true;
            }
            maxLen = Math.max(maxLen, len);
        }
        return maxLen;
    }
}
# @lc code=end