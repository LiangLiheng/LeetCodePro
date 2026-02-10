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
        vector<pair<int, int>> directions = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
        auto idx = [&](int i, int j, int d, int p) -> int {
            return ((i * m + j) * 4 + d) * 2 + p;
        };
        vector<int> dpm(n * m * 8, 0);

        // d=0 DR (1,1)
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                for (int p = 0; p < 2; ++p) {
                    int expn = p ? 2 : 0;
                    int ni = i + 1;
                    int nj = j + 1;
                    if (ni < n && nj < m && grid[ni][nj] == expn) {
                        int np = 1 - p;
                        dpm[idx(i, j, 0, p)] = 1 + dpm[idx(ni, nj, 0, np)];
                    }
                }
            }
        }
        // d=1 DL (1,-1)
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 0; j < m; ++j) {
                for (int p = 0; p < 2; ++p) {
                    int expn = p ? 2 : 0;
                    int ni = i + 1;
                    int nj = j - 1;
                    if (ni < n && nj >= 0 && nj < m && grid[ni][nj] == expn) {
                        dpm[idx(i, j, 1, p)] = 1 + dpm[idx(ni, nj, 1, 1 - p)];
                    }
                }
            }
        }
        // d=2 UL (-1,-1)
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int p = 0; p < 2; ++p) {
                    int expn = p ? 2 : 0;
                    int ni = i - 1;
                    int nj = j - 1;
                    if (ni >= 0 && nj >= 0 && grid[ni][nj] == expn) {
                        dpm[idx(i, j, 2, p)] = 1 + dpm[idx(ni, nj, 2, 1 - p)];
                    }
                }
            }
        }
        // d=3 UR (-1,1)
        for (int i = 0; i < n; ++i) {
            for (int j = m - 1; j >= 0; --j) {
                for (int p = 0; p < 2; ++p) {
                    int expn = p ? 2 : 0;
                    int ni = i - 1;
                    int nj = j + 1;
                    if (ni >= 0 && nj < m && grid[ni][nj] == expn) {
                        dpm[idx(i, j, 3, p)] = 1 + dpm[idx(ni, nj, 3, 1 - p)];
                    }
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] != 1) continue;
                ans = std::max(ans, 1);
                for (int d = 0; d < 4; ++d) {
                    // straight
                    int sadd = dpm[idx(i, j, d, 1)];
                    ans = std::max(ans, 1 + sadd);
                    // turns
                    int cr = i, cc = j;
                    int clen = 1;
                    int di = directions[d].first;
                    int dj = directions[d].second;
                    while (true) {
                        int nr = cr + di;
                        int nc = cc + dj;
                        if (nr < 0 || nr >= n || nc < 0 || nc >= m) break;
                        int nidx = clen;
                        int nexp = (nidx % 2 == 0 ? 0 : 2);
                        if (grid[nr][nc] != nexp) break;
                        cr = nr;
                        cc = nc;
                        clen++;
                        int nd = (d + 1) % 4;
                        int sidx = clen;
                        int sp = (sidx % 2 == 0 ? 0 : 1);
                        int tsadd = dpm[idx(cr, cc, nd, sp)];
                        ans = std::max(ans, clen + tsadd);
                    }
                }
            }
        }
        return ans;
    }
};
# @lc code=end