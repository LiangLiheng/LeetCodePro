#
# @lc app=leetcode id=3544 lang=cpp
#
# [3544] Subtree Inversion Sum
#

# @lc code=start
class Solution {
public:
    long long subtreeInversionSum(vector<vector<int>>& edges, vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<vector<int>> child(n);
        auto build = [&](auto&& self, int u, int p) -> void {
            for (int v : adj[u]) {
                if (v != p) {
                    child[u].push_back(v);
                    self(self, v, u);
                }
            }
        };
        build(build, 0, -1);
        long long sentinel = LLONG_MIN / 2;
        vector<vector<vector<long long>>> memo(n, vector<vector<long long>>(k + 1, vector<long long>(2, sentinel)));
        auto dfs = [&](auto&& self, int u, int d, int f) -> long long {
            if (memo[u][d][f] != sentinel) {
                return memo[u][d][f];
            }
            long long res = sentinel;
            // inv = 0
            {
                int invv = 0;
                int parity = (f + invv) % 2;
                long long contrib = (long long)nums[u] * (parity == 0 ? 1LL : -1LL);
                int f_child = (f + invv) % 2;
                int d_child = invv ? 1 : std::min(d + 1, k);
                long long sub = 0;
                for (int v : child[u]) {
                    sub += self(self, v, d_child, f_child);
                }
                res = std::max(res, contrib + sub);
            }
            // inv = 1 if d == k
            if (d == k) {
                int invv = 1;
                int parity = (f + invv) % 2;
                long long contrib = (long long)nums[u] * (parity == 0 ? 1LL : -1LL);
                int f_child = (f + invv) % 2;
                int d_child = 1;
                long long sub = 0;
                for (int v : child[u]) {
                    sub += self(self, v, d_child, f_child);
                }
                res = std::max(res, contrib + sub);
            }
            memo[u][d][f] = res;
            return res;
        };
        return dfs(dfs, 0, k, 0);
    }
};
# @lc code=end