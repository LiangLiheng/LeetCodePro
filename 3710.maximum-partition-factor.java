#
# @lc app=leetcode id=3710 lang=java
#
# [3710] Maximum Partition Factor
#

# @lc code=start
class Solution {
    public int maxPartitionFactor(int[][] points) {
        int n = points.length;
        if (n == 2) {
            return 0;
        }
        long left = 0;
        long right = 400000001L;
        while (left < right) {
            long mid = left + (right - left + 1) / 2;
            if (check(points, mid, n)) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        return (int) left;
    }
    private boolean check(int[][] points, long k, int n) {
        int[] color = new int[n];
        for (int i = 0; i < n; i++) {
            color[i] = -1;
        }
        for (int i = 0; i < n; i++) {
            if (color[i] == -1) {
                int[] queue = new int[n];
                int front = 0;
                int rear = 0;
                queue[rear++] = i;
                color[i] = 0;
                while (front < rear) {
                    int u = queue[front++];
                    for (int v = 0; v < n; v++) {
                        if (u == v) continue;
                        long dx = Math.abs((long) points[u][0] - points[v][0]);
                        long dy = Math.abs((long) points[u][1] - points[v][1]);
                        if (dx + dy < k) {
                            if (color[v] == -1) {
                                color[v] = 1 - color[u];
                                queue[rear++] = v;
                            } else if (color[v] == color[u]) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }
}
# @lc code=end