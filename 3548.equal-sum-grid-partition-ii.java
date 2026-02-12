#
# @lc app=leetcode id=3548 lang=java
#
# [3548] Equal Sum Grid Partition II
#
# @lc code=start
class Solution {
    public boolean canPartitionGrid(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        long[] rowSum = new long[m];
        long[] colSum = new long[n];
        long total = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                rowSum[i] += grid[i][j];
                colSum[j] += grid[i][j];
                total += grid[i][j];
            }
        }
        // Horizontal cuts
        long sumTop = 0;
        for (int cut = 0; cut < m - 1; ++cut) {
            sumTop += rowSum[cut];
            long sumBot = total - sumTop;
            if (sumTop == sumBot) return true;
            long diff = Math.abs(sumTop - sumBot);
            // Consider discounting a border cell and check constraints
            for (int j = 0; j < n; ++j) {
                // Discount cell from top section's border
                if (sumTop > sumBot && grid[cut][j] == diff && isSectionConnectedAfterRemoval(grid, 0, 0, cut, n, cut, j)) return true;
                // Discount cell from bottom section's border
                if (sumBot > sumTop && grid[cut+1][j] == diff && isSectionConnectedAfterRemoval(grid, cut+1, 0, m, n, cut+1, j)) return true;
            }
        }
        // Vertical cuts
        long sumLeft = 0;
        for (int cut = 0; cut < n - 1; ++cut) {
            sumLeft += colSum[cut];
            long sumRight = total - sumLeft;
            if (sumLeft == sumRight) return true;
            long diff = Math.abs(sumLeft - sumRight);
            // Consider discounting a border cell and check constraints
            for (int i = 0; i < m; ++i) {
                // Discount cell from left section's border
                if (sumLeft > sumRight && grid[i][cut] == diff && isSectionConnectedAfterRemoval(grid, 0, 0, m, cut+1, i, cut)) return true;
                // Discount cell from right section's border
                if (sumRight > sumLeft && grid[i][cut+1] == diff && isSectionConnectedAfterRemoval(grid, 0, cut+1, m, n, i, cut+1)) return true;
            }
        }
        return false;
    }
    // General helper to check if removing cell (remRow, remCol) from section [row0,row1)x[col0,col1) leaves it connected
    private boolean isSectionConnectedAfterRemoval(int[][] grid, int row0, int col0, int row1, int col1, int remRow, int remCol) {
        int m = row1 - row0, n = col1 - col0;
        boolean[][] visited = new boolean[m][n];
        int cnt = 0, total = 0;
        int[] dr = {-1,1,0,0};
        int[] dc = {0,0,-1,1};
        // Count how many cells in section after removal
        for (int i = row0; i < row1; ++i) for (int j = col0; j < col1; ++j) if (!(i == remRow && j == remCol)) ++total;
        // Start BFS from any cell in section besides the removed cell
        outer: for (int i = row0; i < row1; ++i)
            for (int j = col0; j < col1; ++j)
                if (!(i == remRow && j == remCol)) {
                    java.util.Queue<int[]> q = new java.util.LinkedList<>();
                    q.offer(new int[]{i-row0, j-col0});
                    visited[i-row0][j-col0] = true;
                    cnt = 1;
                    while (!q.isEmpty()) {
                        int[] cur = q.poll();
                        for (int d = 0; d < 4; ++d) {
                            int ni = cur[0]+dr[d], nj = cur[1]+dc[d];
                            int ai = ni+row0, aj = nj+col0;
                            if (0 <= ni && ni < m && 0 <= nj && nj < n && !(ai == remRow && aj == remCol) && !visited[ni][nj]) {
                                visited[ni][nj] = true;
                                q.offer(new int[]{ni, nj});
                                ++cnt;
                            }
                        }
                    }
                    break outer;
                }
        return cnt == total;
    }
}
# @lc code=end