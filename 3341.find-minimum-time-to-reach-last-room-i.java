#
# @lc app=leetcode id=3341 lang=java
#
# [3341] Find Minimum Time to Reach Last Room I
#
# @lc code=start
import java.util.*;
class Solution {
    public int minTimeToReach(int[][] moveTime) {
        int n = moveTime.length, m = moveTime[0].length;
        // Validate input
        if (n < 2 || m < 2) return -1;
        for (int[] row : moveTime) {
            if (row.length != m) return -1;
            for (int cell : row) if (cell < 0) return -1;
        }
        int[][] minTime = new int[n][m];
        for (int[] row : minTime) Arrays.fill(row, Integer.MAX_VALUE);
        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));
        pq.offer(new int[]{0, 0, 0}); // {time, x, y}
        minTime[0][0] = 0;
        int[][] dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        while (!pq.isEmpty()) {
            int[] curr = pq.poll();
            int time = curr[0], x = curr[1], y = curr[2];
            if (x == n-1 && y == m-1) {
                // Final verification: ensure this is indeed the minimal time
                // as Dijkstra's always expands the node with minimal time
                return time;
            }
            for (int[] d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    int arrive = Math.max(time + 1, moveTime[nx][ny]);
                    if (arrive < minTime[nx][ny]) {
                        minTime[nx][ny] = arrive;
                        pq.offer(new int[]{arrive, nx, ny});
                    }
                }
            }
        }
        // Edge case: unreachable
        return -1;
    }
}
# @lc code=end