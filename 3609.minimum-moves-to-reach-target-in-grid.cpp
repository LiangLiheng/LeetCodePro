#
# @lc app=leetcode id=3609 lang=cpp
#
# [3609] Minimum Moves to Reach Target in Grid
#
# @lc code=start
class Solution {
public:
    int minMoves(int sx, int sy, int tx, int ty) {
        int moves = 0;
        
        while (tx != sx || ty != sy) {
            if (tx < sx || ty < sy) {
                return -1;
            }
            
            if (tx == ty) {
                return -1;
            }
            
            if (tx > ty) {
                if (ty == sy) {
                    // Check if we can reach tx from sx
                    // At (sx, sy), if sy >= sx, max = sy, else max = sx
                    int step_size = (ty >= sx) ? ty : sx;
                    if ((tx - sx) % step_size == 0) {
                        return moves + (tx - sx) / step_size;
                    } else {
                        return -1;
                    }
                }
                // Reduce tx by subtracting ty multiple times
                int steps = (tx - ty) / ty;
                if (tx - steps * ty < sx) {
                    steps = (tx - sx) / ty;
                }
                if (steps == 0) steps = 1;
                moves += steps;
                tx -= steps * ty;
            } else {
                if (tx == sx) {
                    // Check if we can reach ty from sy
                    // At (sx, sy), if sx >= sy, max = sx, else max = sy
                    int step_size = (tx >= sy) ? tx : sy;
                    if ((ty - sy) % step_size == 0) {
                        return moves + (ty - sy) / step_size;
                    } else {
                        return -1;
                    }
                }
                // Reduce ty by subtracting tx multiple times
                int steps = (ty - tx) / tx;
                if (ty - steps * tx < sy) {
                    steps = (ty - sy) / tx;
                }
                if (steps == 0) steps = 1;
                moves += steps;
                ty -= steps * tx;
            }
        }
        
        return moves;
    }
};
# @lc code=end