#
# @lc app=leetcode id=3609 lang=java
#
# [3609] Minimum Moves to Reach Target in Grid
#

# @lc code=start
class Solution {
    public int minMoves(int sx, int sy, int tx, int ty) {
        if (sx == tx && sy == ty) {
            return 0;
        }
        java.util.Queue<int[]> q = new java.util.ArrayDeque<int[]>();
        java.util.Set<java.lang.Long> vis = new java.util.HashSet<java.lang.Long>();
        long key = ((long) sx << 32) | sy;
        vis.add(key);
        q.offer(new int[]{sx, sy, 0});
        while (!q.isEmpty()) {
            int[] cur = q.poll();
            int x = cur[0];
            int y = cur[1];
            int steps = cur[2];
            int m = Math.max(x, y);
            // move x
            long nextX = (long) x + m;
            long nextY = y;
            if (nextX <= tx && nextY <= ty) {
                long nkey = (nextX << 32) | nextY;
                if (!vis.contains(nkey)) {
                    if (nextX == tx && nextY == ty) {
                        return steps + 1;
                    }
                    vis.add(nkey);
                    q.offer(new int[]{(int) nextX, (int) nextY, steps + 1});
                }
            }
            // move y
            nextX = x;
            nextY = (long) y + m;
            if (nextX <= tx && nextY <= ty) {
                long nkey = (nextX << 32) | nextY;
                if (!vis.contains(nkey)) {
                    if (nextX == tx && nextY == ty) {
                        return steps + 1;
                    }
                    vis.add(nkey);
                    q.offer(new int[]{(int) nextX, (int) nextY, steps + 1});
                }
            }
        }
        return -1;
    }
}
# @lc code=end