#
# @lc app=leetcode id=3493 lang=cpp
#
# [3493] Properties Graph
#

# @lc code=start
class Solution {
public:
    int numberOfComponents(vector<vector<int>>& properties, int k) {
        int n = properties.size();
        vector<bitset<101>> bs(n);
        for (int i = 0; i < n; ++i) {
            for (int val : properties[i]) {
                bs[i][val] = true;
            }
        }
        vector<int> parent(n);
        vector<int> rankk(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
        auto find = [&](auto&& self, int x) -> int {
            return parent[x] != x ? parent[x] = self(self, parent[x]) : x;
        };
        auto union_sets = [&](int x, int y) {
            int px = find(find, x);
            int py = find(find, y);
            if (px == py) return;
            if (rankk[px] < rankk[py]) swap(px, py);
            parent[py] = px;
            if (rankk[px] == rankk[py]) ++rankk[px];
        };
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if ((bs[i] & bs[j]).count() >= static_cast<size_t>(k)) {
                    union_sets(i, j);
                }
            }
        }
        int components = 0;
        for (int i = 0; i < n; ++i) {
            if (find(find, i) == i) ++components;
        }
        return components;
    }
};
# @lc code=end