# @lc app=leetcode id=3609 lang=java
#
# [3609] Minimum Moves to Reach Target in Grid
#
# @lc code=start
class Solution {
    public int minMoves(int sx, int sy, int tx, int ty) {
        int moves = 0;
        while (tx > sx || ty > sy) {
            // If tx >= ty and tx > sx, try to move x backward
            if (tx >= ty && tx > sx) {
                int m = Math.max(tx, ty);
                int prev_tx = tx - m;
                if (prev_tx >= sx && ty >= sy && m == Math.max(prev_tx, ty)) {
                    tx = prev_tx;
                    moves++;
                    continue;
                } else {
                    return -1;
                }
            }
            // If ty > tx and ty > sy, try to move y backward
            if (ty > tx && ty > sy) {
                int m = Math.max(tx, ty);
                int prev_ty = ty - m;
                if (tx >= sx && prev_ty >= sy && m == Math.max(tx, prev_ty)) {
                    ty = prev_ty;
                    moves++;
                    continue;
                } else {
                    return -1;
                }
            }
            // If neither move is possible, return -1
            return -1;
        }
        // Final state verification
        return (tx == sx && ty == sy) ? moves : -1;
    }
}
# @lc code=end