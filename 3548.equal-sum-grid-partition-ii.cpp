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
        const int MAXV = 100000;
        vector<long long> prefix_row(m + 1, 0);
        for (int i = 0; i < m; ++i) {
            long long rowsum = 0;
            for (int j = 0; j < n; ++j) {
                rowsum += grid[i][j];
            }
            prefix_row[i + 1] = prefix_row[i] + rowsum;
        }
        long long S = prefix_row[m];
        vector<long long> prefix_col(n + 1, 0);
        for (int j = 0; j < n; ++j) {
            long long colsum = 0;
            for (int i = 0; i < m; ++i) {
                colsum += grid[i][j];
            }
            prefix_col[j + 1] = prefix_col[j] + colsum;
        }
        vector<vector<int>> row_pos(MAXV + 1);
        vector<vector<int>> col_pos(MAXV + 1);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int v = grid[i][j];
                row_pos[v].push_back(i);
                col_pos[v].push_back(j);
            }
        }
        for (int v = 0; v <= MAXV; ++v) {
            sort(row_pos[v].begin(), row_pos[v].end());
            sort(col_pos[v].begin(), col_pos[v].end());
        }
        // Horizontal cuts
        for (int k = 1; k < m; ++k) {
            long long sum_top = prefix_row[k];
            long long sum_bot = S - sum_top;
            if (sum_top == sum_bot) return true;
            if (sum_top > sum_bot) {
                long long diff = sum_top - sum_bot;
                if (diff > MAXV) continue;
                int h = k, w = n;
                bool thick = (h >= 2 && w >= 2);
                int vv = (int)diff;
                if (thick) {
                    auto& lis = row_pos[vv];
                    auto it = lower_bound(lis.begin(), lis.end(), k);
                    if (it != lis.begin()) return true;
                } else {
                    if (w == 1) {
                        if ((long long)grid[0][0] == diff || (long long)grid[k - 1][0] == diff) return true;
                    } else {
                        if ((long long)grid[0][0] == diff || (long long)grid[0][n - 1] == diff) return true;
                    }
                }
            } else if (sum_bot > sum_top) {
                long long diff = sum_bot - sum_top;
                if (diff > MAXV) continue;
                int h = m - k, w = n;
                bool thick = (h >= 2 && w >= 2);
                int vv = (int)diff;
                if (thick) {
                    auto& lis = row_pos[vv];
                    auto it = lower_bound(lis.begin(), lis.end(), k);
                    if (it != lis.end()) return true;
                } else {
                    if (w == 1) {
                        if ((long long)grid[k][0] == diff || (long long)grid[m - 1][0] == diff) return true;
                    } else {
                        if ((long long)grid[m - 1][0] == diff || (long long)grid[m - 1][n - 1] == diff) return true;
                    }
                }
            }
        }
        // Vertical cuts
        for (int k = 1; k < n; ++k) {
            long long sum_left = prefix_col[k];
            long long sum_right = S - sum_left;
            if (sum_left == sum_right) return true;
            if (sum_left > sum_right) {
                long long diff = sum_left - sum_right;
                if (diff > MAXV) continue;
                int hh = m, ww = k;
                bool thick = (hh >= 2 && ww >= 2);
                int vv = (int)diff;
                if (thick) {
                    auto& lis = col_pos[vv];
                    auto it = lower_bound(lis.begin(), lis.end(), k);
                    if (it != lis.begin()) return true;
                } else {
                    if (hh == 1) {
                        if ((long long)grid[0][0] == diff || (long long)grid[0][k - 1] == diff) return true;
                    } else {
                        if ((long long)grid[0][0] == diff || (long long)grid[m - 1][0] == diff) return true;
                    }
                }
            } else if (sum_right > sum_left) {
                long long diff = sum_right - sum_left;
                if (diff > MAXV) continue;
                int hh = m, ww = n - k;
                bool thick = (hh >= 2 && ww >= 2);
                int vv = (int)diff;
                if (thick) {
                    auto& lis = col_pos[vv];
                    auto it = lower_bound(lis.begin(), lis.end(), k);
                    if (it != lis.end()) return true;
                } else {
                    if (hh == 1) {
                        if ((long long)grid[0][k] == diff || (long long)grid[0][n - 1] == diff) return true;
                    } else {
                        if ((long long)grid[0][n - 1] == diff || (long long)grid[m - 1][n - 1] == diff) return true;
                    }
                }
            }
        }
        return false;
    }
};
# @lc code=end