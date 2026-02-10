#
# @lc app=leetcode id=3548 lang=cpp
#
# [3548] Equal Sum Grid Partition II
#
# @lc code=start
class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // Try horizontal cuts
        for (int cut_row = 0; cut_row < m - 1; cut_row++) {
            if (checkHorizontalCut(grid, cut_row, m, n)) {
                return true;
            }
        }
        
        // Try vertical cuts
        for (int cut_col = 0; cut_col < n - 1; cut_col++) {
            if (checkVerticalCut(grid, cut_col, m, n)) {
                return true;
            }
        }
        
        return false;
    }
    
private:
    bool checkHorizontalCut(vector<vector<int>>& grid, int cut_row, int m, int n) {
        long long top_sum = 0, bottom_sum = 0;
        
        for (int i = 0; i <= cut_row; i++) {
            for (int j = 0; j < n; j++) {
                top_sum += grid[i][j];
            }
        }
        
        for (int i = cut_row + 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                bottom_sum += grid[i][j];
            }
        }
        
        if (top_sum == bottom_sum) return true;
        
        for (int i = 0; i <= cut_row; i++) {
            for (int j = 0; j < n; j++) {
                if (top_sum - grid[i][j] == bottom_sum) {
                    if (isConnected(grid, i, j, 0, cut_row, 0, n-1)) {
                        return true;
                    }
                }
            }
        }
        
        for (int i = cut_row + 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (bottom_sum - grid[i][j] == top_sum) {
                    if (isConnected(grid, i, j, cut_row+1, m-1, 0, n-1)) {
                        return true;
                    }
                }
            }
        }
        
        return false;
    }
    
    bool checkVerticalCut(vector<vector<int>>& grid, int cut_col, int m, int n) {
        long long left_sum = 0, right_sum = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j <= cut_col; j++) {
                left_sum += grid[i][j];
            }
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = cut_col + 1; j < n; j++) {
                right_sum += grid[i][j];
            }
        }
        
        if (left_sum == right_sum) return true;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j <= cut_col; j++) {
                if (left_sum - grid[i][j] == right_sum) {
                    if (isConnected(grid, i, j, 0, m-1, 0, cut_col)) {
                        return true;
                    }
                }
            }
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = cut_col + 1; j < n; j++) {
                if (right_sum - grid[i][j] == left_sum) {
                    if (isConnected(grid, i, j, 0, m-1, cut_col+1, n-1)) {
                        return true;
                    }
                }
            }
        }
        
        return false;
    }
    
    bool isConnected(vector<vector<int>>& grid, int rem_i, int rem_j,
                     int r_start, int r_end, int c_start, int c_end) {
        int total = (r_end - r_start + 1) * (c_end - c_start + 1) - 1;
        if (total == 0) return true;
        
        int si = -1, sj = -1;
        for (int i = r_start; i <= r_end && si == -1; i++) {
            for (int j = c_start; j <= c_end; j++) {
                if (i != rem_i || j != rem_j) {
                    si = i; sj = j; break;
                }
            }
        }
        
        queue<pair<int, int>> q;
        set<pair<int, int>> vis;
        q.push({si, sj});
        vis.insert({si, sj});
        
        int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        
        while (!q.empty()) {
            auto [ci, cj] = q.front();
            q.pop();
            
            for (int d = 0; d < 4; d++) {
                int ni = ci + dirs[d][0];
                int nj = cj + dirs[d][1];
                
                if (ni >= r_start && ni <= r_end && nj >= c_start && nj <= c_end &&
                    (ni != rem_i || nj != rem_j) && vis.find({ni, nj}) == vis.end()) {
                    vis.insert({ni, nj});
                    q.push({ni, nj});
                }
            }
        }
        
        return vis.size() == total;
    }
};
# @lc code=end