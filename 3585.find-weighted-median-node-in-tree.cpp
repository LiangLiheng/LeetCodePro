#
# @lc app=leetcode id=3585 lang=cpp
#
# [3585] Find Weighted Median Node in Tree
#

# @lc code=start
class Solution {
public:
    vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        using ll = long long;
        const int LOG = 20;
        vector<vector<pair<int, ll>>> adj(n);
        for (const auto& e : edges) {
            int a = e[0], b = e[1];
            ll w = e[2];
            adj[a].emplace_back(b, w);
            adj[b].emplace_back(a, w);
        }
        vector<int> depth(n);
        vector<ll> dist(n);
        vector<vector<int>> par(LOG, vector<int>(n, -1));
        vector<bool> vis(n, false);
        queue<int> q;
        q.push(0);
        vis[0] = true;
        depth[0] = 0;
        dist[0] = 0;
        par[0][0] = -1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto [v, w] : adj[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    depth[v] = depth[u] + 1;
                    dist[v] = dist[u] + w;
                    par[0][v] = u;
                    q.push(v);
                }
            }
        }
        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                int p = par[k - 1][i];
                if (p != -1) {
                    par[k][i] = par[k - 1][p];
                } else {
                    par[k][i] = -1;
                }
            }
        }
        auto get_lca = [&](int uu_, int vv_) -> int {
            int x = uu_, y = vv_;
            if (depth[x] > depth[y]) {
                x = vv_;
                y = uu_;
            }
            // now depth[x] <= depth[y]
            for (int k = LOG - 1; k >= 0; k--) {
                if (par[k][y] != -1 && depth[par[k][y]] >= depth[x]) {
                    y = par[k][y];
                }
            }
            if (x == y) return x;
            for (int k = LOG - 1; k >= 0; k--) {
                if (par[k][x] != par[k][y]) {
                    x = par[k][x];
                    y = par[k][y];
                }
            }
            return par[0][x];
        };
        vector<int> ans;
        ans.reserve(queries.size());
        for (const auto& qu : queries) {
            int u = qu[0], v = qu[1];
            int L = get_lca(u, v);
            ll Su = dist[u], Sv = dist[v], SL = dist[L];
            ll S = Su + Sv - 2 * SL;
            ll targ = (S + 1) / 2;
            ll preL = Su - SL;
            int node;
            if (preL >= targ) {
                ll maxd = Su - targ;
                int xx = u;
                for (int k = LOG - 1; k >= 0; k--) {
                    int anc = par[k][xx];
                    if (anc != -1 && depth[anc] >= depth[L] && dist[anc] > maxd) {
                        xx = anc;
                    }
                }
                if (dist[xx] <= maxd) {
                    node = xx;
                } else {
                    node = par[0][xx];
                }
            } else {
                ll mind = targ - preL + SL;
                int yy = v;
                for (int k = LOG - 1; k >= 0; k--) {
                    int anc = par[k][yy];
                    if (anc != -1 && depth[anc] >= depth[L] && dist[anc] >= mind) {
                        yy = anc;
                    }
                }
                node = yy;
            }
            ans.push_back(node);
        }
        return ans;
    }
};
# @lc code=end