#
# @lc app=leetcode id=3515 lang=cpp
#
# [3515] Shortest Path in a Weighted Tree
#

# @lc code=start
class Solution {
public:
    vector<int> treeQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        if (n == 0) return {};
        vector<vector<pair<int, int>>> adj(n + 1);
        for (const auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        vector<int> parent(n + 1, 0);
        vector<int> edge_w(n + 1, 0);
        vector<vector<int>> childs(n + 1);
        vector<char> vis(n + 1, 0);
        queue<int> qq;
        qq.push(1);
        vis[1] = 1;
        while (!qq.empty()) {
            int u = qq.front(); qq.pop();
            for (auto& p : adj[u]) {
                int v = p.first;
                if (!vis[v]) {
                    vis[v] = 1;
                    parent[v] = u;
                    edge_w[v] = p.second;
                    childs[u].push_back(v);
                    qq.push(v);
                }
            }
        }
        vector<int> tin(n + 1), tout(n + 1);
        int timer = 1;
        stack<pair<int, int>> stk;  // {node, next_child_idx}
        stk.push({1, 0});
        tin[1] = timer++;
        while (!stk.empty()) {
            auto& curr = stk.top();
            int u = curr.first;
            int& cidx = curr.second;
            if (cidx < childs[u].size()) {
                int v = childs[u][cidx];
                ++cidx;
                stk.push({v, 0});
                tin[v] = timer++;
            } else {
                tout[u] = timer;
                stk.pop();
            }
        }
        struct FenwickTree {
            vector<long long> tree;
            int nn;
            FenwickTree(int _n) : nn(_n), tree(_n + 2, 0LL) {}
            void upd(int i, long long val) {
                while (i <= nn) {
                    tree[i] += val;
                    i += i & -i;
                }
            }
            long long qy(int i) {
                long long res = 0;
                while (i > 0) {
                    res += tree[i];
                    i -= i & -i;
                }
                return res;
            }
        };
        FenwickTree ft(n);
        for (int c = 2; c <= n; ++c) {
            int l = tin[c], r = tout[c] - 1;
            long long w = edge_w[c];
            ft.upd(l, w);
            if (r + 1 <= n) ft.upd(r + 1, -w);
        }
        vector<int> answer;
        for (const auto& que : queries) {
            if (que[0] == 2) {
                int x = que[1];
                answer.push_back(static_cast<int>(ft.qy(tin[x])));
            } else {
                int u = que[1], v = que[2], nw = que[3];
                int child = (parent[v] == u ? v : u);
                long long oldw = edge_w[child];
                long long del = static_cast<long long>(nw) - oldw;
                edge_w[child] = nw;
                int l = tin[child], r = tout[child] - 1;
                ft.upd(l, del);
                if (r + 1 <= n) ft.upd(r + 1, -del);
            }
        }
        return answer;
    }
};
# @lc code=end