#
# @lc app=leetcode id=3464 lang=cpp
#
# [3464] Maximize the Distance Between Points on a Square
#
# @lc code=start
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxDistance(int side_, vector<vector<int>>& points, int k) {
        long long S = side_;
        vector<vector<long long>> sides(4);
        for (auto& pt : points) {
            long long x = pt[0], y = pt[1];
            if (y == 0) sides[0].push_back(x);
            else if (x == S) sides[1].push_back(y);
            else if (y == S) sides[2].push_back(x);
            else sides[3].push_back(y);
        }
        for (int i = 0; i < 4; ++i) {
            sort(sides[i].begin(), sides[i].end());
        }
        long long lo = 0, hi = 2 * S;
        while (lo < hi) {
            long long mid = (lo + hi + 1) / 2;
            if (check(sides, S, mid, k)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return lo;
    }
private:
    bool check(const vector<vector<long long>>& sides, long long S, long long D, int K) {
        vector<int> maxsel(4);
        for (int i = 0; i < 4; ++i) {
            maxsel[i] = get_maxsel(sides[i], D);
        }
        vector<vector<array<long long, 4>>> ranges(4, vector<array<long long, 4>>(26, {-1LL,-1LL,-1LL,-1LL}));
        for (int i = 0; i < 4; ++i) {
            const auto& p = sides[i];
            int m = p.size();
            if (m == 0) continue;
            // suffix[j]: max sel starting from j
            vector<int> suffix(m);
            for (int j = m - 1; j >= 0; --j) {
                long long nmin = p[j] + D;
                auto it = lower_bound(p.begin() + j + 1, p.end(), nmin);
                int nxt = it - p.begin();
                suffix[j] = (nxt < m ? 1 + suffix[nxt] : 1);
            }
            // prefix[j]: max sel up to j
            vector<int> prefix(m);
            int curcnt = 0;
            long long lastp = -3000000000LL;
            for (int j = 0; j < m; ++j) {
                if (p[j] - lastp >= D) {
                    ++curcnt;
                    lastp = p[j];
                }
                prefix[j] = curcnt;
            }
            // for each si
            for (int si = 1; si <= min(25, m); ++si) {
                // L starts: possible leftmost positions
                int jmin = -1, jmax = -1;
                for (int j = 0; j < m; ++j) {
                    if (suffix[j] >= si) {
                        if (jmin == -1) jmin = j;
                        jmax = j;
                    }
                }
                long long minl = -1, maxl = -1;
                if (jmin != -1) {
                    minl = p[jmin];
                    maxl = p[jmax];
                }
                // R ends: possible rightmost positions
                int vmin = -1, vmax = -1;
                for (int v = 0; v < m; ++v) {
                    if (prefix[v] >= si) {
                        if (vmin == -1) vmin = v;
                        vmax = v;
                    }
                }
                long long minr = -1, maxr = -1;
                if (vmin != -1) {
                    minr = p[vmin];
                    maxr = p[vmax];
                }
                ranges[i][si] = {minl, maxl, minr, maxr};
            }
        }
        // enumerate dist
        for (int s0 = 0; s0 <= K; ++s0) {
            if (s0 > maxsel[0]) continue;
            for (int s1 = 0; s1 <= K - s0; ++s1) {
                if (s1 > maxsel[1]) continue;
                for (int s2 = 0; s2 <= K - s0 - s1; ++s2) {
                    int s3 = K - s0 - s1 - s2;
                    if (s3 > maxsel[3] || s3 < 0) continue;
                    array<int, 4> ss = {s0, s1, s2, s3};
                    if (!valid_ranges(ranges, ss, D)) continue;
                    // 4 configs
                    for (int cbt = 0; cbt < 2; ++cbt) {
                        for (int clr = 0; clr < 2; ++clr) {
                            if (check_constraints(ranges, ss, S, D, cbt, clr)) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
    int get_maxsel(const vector<long long>& p, long long D) {
        int m = p.size();
        if (m == 0) return 0;
        int cnt = 1;
        long long last = p[0];
        for (int i = 1; i < m; ++i) {
            if (p[i] - last >= D) {
                ++cnt;
                last = p[i];
            }
        }
        return cnt;
    }
    bool valid_ranges(const vector<vector<array<long long, 4>>>& ranges, const array<int, 4>& s, long long D) {
        for (int i = 0; i < 4; ++i) {
            int si = s[i];
            if (si == 0) continue;
            auto r = ranges[i][si];
            if (r[0] < 0) return false;
            // Removed buggy: if (r[1] > r[2]) return false; (false neg on multi-subset extremals)
            if (si >= 2 && r[3] - r[0] < (si - 1LL) * D) return false;
        }
        return true;
    }
    bool check_constraints(const vector<vector<array<long long, 4>>>& ranges, const array<int, 4>& s, long long S, long long D, int cbt, int clr) {
        long long T = max(0LL, D - S);
        long long c_adj = D - S;
        long long U = 2 * S - D;
        // A1 bottom-left
        if (s[0] > 0 && s[3] > 0) {
            auto r0 = ranges[0][s[0]];
            auto r3 = ranges[3][s[3]];
            if (r0[1] + r3[1] < D) return false;
        }
        // A2 bottom-right
        if (s[0] > 0 && s[1] > 0) {
            auto r0 = ranges[0][s[0]];
            auto r1 = ranges[1][s[1]];
            if (r1[1] < c_adj + r0[2]) return false;
        }
        // A3 right-top
        if (s[1] > 0 && s[2] > 0) {
            auto r1 = ranges[1][s[1]];
            auto r2 = ranges[2][s[2]];
            if (r1[2] + r2[2] > U) return false;
        }
        // A4 top-left
        if (s[2] > 0 && s[3] > 0) {
            auto r2 = ranges[2][s[2]];
            auto r3 = ranges[3][s[3]];
            if (r2[1] < c_adj + r3[2]) return false;
        }
        // opposite bt
        if (s[0] > 0 && s[2] > 0) {
            auto r0 = ranges[0][s[0]];
            auto r2 = ranges[2][s[2]];
            bool satisfied = (T == 0);
            if (T > 0) {
                if (cbt == 0) {
                    satisfied = (r2[1] >= r0[2] + T);
                } else {
                    satisfied = (r0[1] >= r2[2] + T);
                }
            }
            if (!satisfied) return false;
        }
        // opposite lr
        if (s[1] > 0 && s[3] > 0) {
            auto r1 = ranges[1][s[1]];
            auto r3 = ranges[3][s[3]];
            bool satisfied = (T == 0);
            if (T > 0) {
                if (clr == 0) {
                    satisfied = (r1[1] >= r3[2] + T);
                } else {
                    satisfied = (r3[1] >= r1[2] + T);
                }
            }
            if (!satisfied) return false;
        }
        return true;
    }
};
# @lc code=end