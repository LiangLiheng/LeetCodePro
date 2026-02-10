#
# @lc app=leetcode id=3367 lang=cpp
#
# [3367] Maximize Sum of Weights after Edge Removals
#

# @lc code=start
class Solution {
public:
    long long maximizeSumOfWeights(vector<vector<int>>& edges, int k) {
        int n = edges.size() + 1;
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        vector<long long> dpA(n), dpC(n);
        auto dfs = [&](auto&& self, int u, int p) -> void {
            vector<long long> benefits;
            long long base = 0;
            for (auto [v, w] : adj[u]) {
                if (v == p) continue;
                self(self, v, u);
                base += dpA[v];
                long long ben = (long long)w + dpC[v] - dpA[v];
                benefits.push_back(ben);
            }
            auto get_extra = [&](int lim) -> long long {
                vector<long long> pos;
                for (auto b : benefits) if (b > 0LL) pos.push_back(b);
                sort(pos.rbegin(), pos.rend());
                long long ex = 0;
                int tk = min((int)pos.size(), lim);
                for (int i = 0; i < tk; ++i) ex += pos[i];
                return ex;
            };
            dpA[u] = base + get_extra(k);
            dpC[u] = base + get_extra(k - 1);
        };
        dfs(dfs, 0, -1);
        return dpA[0];
    }
};
# @lc code=end