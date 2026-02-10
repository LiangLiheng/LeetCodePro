#
# @lc app=leetcode id=3382 lang=cpp
#
# [3382] Maximum Area Rectangle With Point Constraints II
#

# @lc code=start
class Solution {
public:
    long long maxRectangleArea(vector<int>& xCoord, vector<int>& yCoord) {
        int n = xCoord.size();
        if (n < 4) return -1;
        vector<pair<int, int>> pts(n);
        for (int j = 0; j < n; ++j) {
            pts[j] = {xCoord[j], yCoord[j]};
        }
        sort(pts.begin(), pts.end());
        vector<int> all_x;
        for (const auto& p : pts) {
            all_x.push_back(p.first);
        }
        sort(all_x.begin(), all_x.end());
        auto last = unique(all_x.begin(), all_x.end());
        all_x.erase(last, all_x.end());
        int m = all_x.size();
        map<int, int> x_to_idx;
        for (int j = 0; j < m; ++j) {
            x_to_idx[all_x[j]] = j;
        }
        vector<vector<int>> col_ys(m);
        map<pair<int, int>, vector<int>> supp;
        int i = 0;
        while (i < n) {
            int curx = pts[i].first;
            vector<int> ys;
            while (i < n && pts[i].first == curx) {
                ys.push_back(pts[i].second);
                ++i;
            }
            sort(ys.begin(), ys.end());
            int idx = x_to_idx[curx];
            col_ys[idx] = ys;
            for (size_t k = 0; k + 1 < ys.size(); ++k) {
                supp[{ys[k], (int)ys[k + 1]}].push_back(idx);
            }
        }
        int tsz = 1;
        while (tsz < m) tsz <<= 1;
        vector<vector<int>> tree(2 * tsz);
        for (int j = 0; j < m; ++j) {
            tree[tsz + j] = col_ys[j];
        }
        for (int v = tsz - 1; v >= 1; --v) {
            size_t sz = tree[2 * v].size() + tree[2 * v + 1].size();
            tree[v].resize(sz);
            merge(tree[2 * v].begin(), tree[2 * v].end(),
                  tree[2 * v + 1].begin(), tree[2 * v + 1].end(),
                  tree[v].begin());
        }
        auto has_point = [&](auto&& self, int v, int tl, int tr, int l, int r, int yl, int yh) -> bool {
            if (l > r) return false;
            if (tl == l && tr == r) {
                const auto& vec = tree[v];
                auto it = lower_bound(vec.cbegin(), vec.cend(), yl);
                return it != vec.cend() && *it <= yh;
            }
            int tm = (tl + tr) / 2;
            if (self(self, 2 * v, tl, tm, l, min(r, tm), yl, yh)) return true;
            return self(self, 2 * v + 1, tm + 1, tr, max(l, tm + 1), r, yl, yh);
        };
        long long ans = -1;
        for (const auto& entry : supp) {
            int yl = entry.first.first;
            int yh = entry.first.second;
            vector<int>& Svec = entry.second;
            if (Svec.size() < 2) continue;
            sort(Svec.begin(), Svec.end());
            for (size_t k = 0; k + 1 < Svec.size(); ++k) {
                int ia = Svec[k];
                int ib = Svec[k + 1];
                int L = ia + 1;
                int R = ib - 1;
                bool hasp = (L <= R) && has_point(has_point, 1, 0, tsz - 1, L, R, yl, yh);
                if (!hasp) {
                    long long width = (long long)all_x[ib] - all_x[ia];
                    long long height = (long long)yh - yl;
                    long long area = width * height;
                    if (area > ans) ans = area;
                }
            }
        }
        return ans;
    }
};
# @lc code=end