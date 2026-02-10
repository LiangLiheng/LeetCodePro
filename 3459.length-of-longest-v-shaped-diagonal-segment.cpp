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
        
        // Direction vectors: down-right, down-left, up-left, up-right
        vector<pair<int,int>> dirs = {{1,1}, {1,-1}, {-1,-1}, {-1,1}};
        
        // Clockwise turn: 0->1, 1->2, 2->3, 3->0
        vector<int> clockwise = {1, 2, 3, 0};
        
        // Expected value at position idx in sequence
        auto getExpected = [](int idx) {
            if (idx == 0) return 1;
            return (idx % 2 == 1) ? 2 : 0;
        };
        
        // Try starting from each cell
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] != 1) continue;
                
                // Try each starting direction
                for (int dir = 0; dir < 4; dir++) {
                    // Extend in the initial direction
                    vector<pair<int,int>> path;
                    int r = i, c = j, idx = 0;
                    
                    while (r >= 0 && r < n && c >= 0 && c < m && 
                           grid[r][c] == getExpected(idx)) {
                        path.push_back({r, c});
                        r += dirs[dir].first;
                        c += dirs[dir].second;
                        idx++;
                    }
                    
                    maxLen = max(maxLen, (int)path.size());
                    
                    // Try turning at each position
                    for (int k = 1; k < path.size(); k++) {
                        int turnR = path[k].first;
                        int turnC = path[k].second;
                        int newDir = clockwise[dir];
                        
                        int r2 = turnR + dirs[newDir].first;
                        int c2 = turnC + dirs[newDir].second;
                        int idx2 = k + 1;
                        int len2 = k + 1;
                        
                        while (r2 >= 0 && r2 < n && c2 >= 0 && c2 < m && 
                               grid[r2][c2] == getExpected(idx2)) {
                            len2++;
                            r2 += dirs[newDir].first;
                            c2 += dirs[newDir].second;
                            idx2++;
                        }
                        
                        maxLen = max(maxLen, len2);
                    }
                }
            }
        }
        
        return maxLen;
    }
};
# @lc code=end