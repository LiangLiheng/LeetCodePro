#
# @lc app=leetcode id=3559 lang=cpp
#
# [3559] Number of Ways to Assign Edge Weights II
#

# @lc code=start
class Solution {
public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        const int MOD = 1000000007;
        const int LOG = 18;
        vector<vector<int>> adj(n + 1);
        for (const auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> depth(n + 1, 0);
        vector<vector<int>> par(LOG, vector<int>(n + 1, 0));
        vector<bool> vis(n + 1, false);
        queue<int> q;
        q.push(1);
        vis[1] = true;
        par[0][1] = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    par[0][v] = u;
                    depth[v] = depth[u] + 1;
                    q.push(v);
                }
            }
        }
        for (int j = 1; j < LOG; j++) {
            for (int i = 1; i <= n; i++) {
                par[j][i] = par[j - 1][par[j - 1][i]];
            }
        }
        vector<long long> pow2(n, 1LL);
        for (int i = 1; i < n; i++) {
            pow2[i] = pow2[i - 1] * 2LL % MOD;
        }
        auto get_lca = [&](int a, int b) -> int {
            int u = a, v = b;
            if (depth[u] > depth[v]) swap(u, v);
            int diff = depth[v] - depth[u];
            for (int j = 0; j < LOG; j++) {
                if ((diff >> j) & 1) {
                    v = par[j][v];
                }
            }
            if (u == v) return u;
            for (int j = LOG - 1; j >= 0; j--) {
                if (par[j][u] != par[j][v]) {
                    u = par[j][u];
                    v = par[j][v];
                }
            }
            return par[0][u];
        };
        vector<int> ans;
        for (const auto& query : queries) {
            int u = query[0], v = query[1];
            int lca_node = get_lca(u, v);
            int k = depth[u] + depth[v] - 2 * depth[lca_node];
            int ways = (k == 0) ? 0 : (pow2[k - 1] % MOD);
            ans.push_back(ways);
        }
        return ans;
    }
};
# @lc code=end