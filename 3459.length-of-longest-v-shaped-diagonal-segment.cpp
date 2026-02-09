#
# @lc app=leetcode id=3459 lang=cpp
#
# [3459] Length of Longest V-Shaped Diagonal Segment
#
# @lc code=start
class Solution {
public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int maxLen = 0;
        
        // Four diagonal directions: down-right, down-left, up-left, up-right
        vector<pair<int, int>> dirs = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
        
        // Get expected value at sequence position idx
        auto getExpected = [](int idx) -> int {
            if (idx == 0) return 1;
            return (idx % 2 == 1) ? 2 : 0;
        };
        
        // Try each cell with value 1 as starting point
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] != 1) continue;
                
                // Try each initial direction
                for (int dir = 0; dir < 4; dir++) {
                    // Case 1: No turn - just go straight
                    int len = 1, x = i, y = j, idx = 1;
                    while (true) {
                        x += dirs[dir].first;
                        y += dirs[dir].second;
                        if (x < 0 || x >= n || y < 0 || y >= m) break;
                        if (grid[x][y] != getExpected(idx)) break;
                        len++;
                        idx++;
                    }
                    maxLen = max(maxLen, len);
                    
                    // Case 2: Turn at some position
                    x = i; y = j; idx = 1;
                    int lenBeforeTurn = 1;
                    
                    while (true) {
                        int nx = x + dirs[dir].first;
                        int ny = y + dirs[dir].second;
                        if (nx < 0 || nx >= n || ny < 0 || ny >= m) break;
                        if (grid[nx][ny] != getExpected(idx)) break;
                        
                        x = nx; y = ny;
                        lenBeforeTurn++;
                        idx++;
                        
                        // Try a 90-degree clockwise turn from current position
                        int newDir = (dir + 1) % 4;
                        int tx = x, ty = y, tidx = idx;
                        int totalLen = lenBeforeTurn;
                        
                        while (true) {
                            tx += dirs[newDir].first;
                            ty += dirs[newDir].second;
                            if (tx < 0 || tx >= n || ty < 0 || ty >= m) break;
                            if (grid[tx][ty] != getExpected(tidx)) break;
                            totalLen++;
                            tidx++;
                        }
                        
                        maxLen = max(maxLen, totalLen);
                    }
                }
            }
        }
        
        return maxLen;
    }
};
# @lc code=end