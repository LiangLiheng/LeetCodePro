#
# @lc app=leetcode id=3625 lang=cpp
#
# [3625] Count Number of Trapezoids II
#

# @lc code=start
class Solution {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        int n = points.size();
        set<pair<int, int>> slopes;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];
                int g = __gcd(abs(dx), abs(dy));
                if (g != 0) {
                    dx /= g;
                    dy /= g;
                }
                if (dx < 0 || (dx == 0 && dy < 0)) {
                    dx = -dx;
                    dy = -dy;
                }
                slopes.emplace(dx, dy);
            }
        }
        using ll = long long;
        ll S = 0;
        for (auto& sl : slopes) {
            int dx = sl.first;
            int dy = sl.second;
            map<ll, int> cnt;
            for (int k = 0; k < n; ++k) {
                ll c = (ll)dy * points[k][0] - (ll)dx * points[k][1];
                ++cnt[c];
            }
            ll tot = 0, sqsum = 0;
            for (auto& p : cnt) {
                int sz = p.second;
                if (sz >= 2) {
                    ll com = (ll)sz * (sz - 1) / 2;
                    tot += com;
                    sqsum += com * com;
                }
            }
            ll local = (tot * tot - sqsum) / 2;
            S += local;
        }
        // Compute T2: number of parallelograms
        map<pair<ll, ll>, vector<pair<int, int>>> midp;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                ll sx = (ll)points[i][0] + points[j][0];
                ll sy = (ll)points[i][1] + points[j][1];
                midp[{sx, sy}].emplace_back(i, j);
            }
        }
        ll T2 = 0;
        for (auto& p : midp) {
            auto& vec = p.second;
            int k = vec.size();
            for (int a = 0; a < k; ++a) {
                for (int b = a + 1; b < k; ++b) {
                    int i1 = vec[a].first, j1 = vec[a].second;
                    int i2 = vec[b].first, j2 = vec[b].second;
                    if (i1 != i2 && i1 != j2 && j1 != i2 && j1 != j2) {
                        ++T2;
                    }
                }
            }
        }
        ll ans = S - T2;
        return (int)ans;
    }
};
# @lc code=end