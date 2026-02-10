#
# @lc app=leetcode id=3695 lang=cpp
#
# [3695] Maximize Alternating Sum Using Swaps
#

# @lc code=start
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums, vector<vector<int>>& swaps) {
        int n = nums.size();
        vector<int> parent(n), rnk(n, 0);
        for (int i = 0; i < n; ++i) parent[i] = i;
        auto find = [&](auto&& self, int x) -> int {
            if (parent[x] != x) {
                parent[x] = self(self, parent[x]);
            }
            return parent[x];
        };
        auto uni = [&](int a, int b) {
            int x = find(find, a);
            int y = find(find, b);
            if (x == y) return;
            if (rnk[x] < rnk[y]) swap(x, y);
            parent[y] = x;
            if (rnk[x] == rnk[y]) ++rnk[x];
        };
        for (const auto& sw : swaps) {
            uni(sw[0], sw[1]);
        }
        vector<vector<int>> comps(n);
        for (int i = 0; i < n; ++i) {
            comps[find(find, i)].push_back(i);
        }
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            if (comps[i].empty()) continue;
            const auto& indices = comps[i];
            vector<long long> vals;
            for (int idx : indices) {
                vals.push_back(nums[idx]);
            }
            sort(vals.rbegin(), vals.rend());
            int even_cnt = 0;
            for (int idx : indices) {
                if (idx % 2 == 0) ++even_cnt;
            }
            long long contrib = 0;
            for (size_t j = 0; j < vals.size(); ++j) {
                if (j < even_cnt) {
                    contrib += vals[j];
                } else {
                    contrib -= vals[j];
                }
            }
            ans += contrib;
        }
        return ans;
    }
};
# @lc code=end