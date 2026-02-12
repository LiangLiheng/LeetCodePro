#
# @lc app=leetcode id=3559 lang=java
#
# [3559] Number of Ways to Assign Edge Weights II
#
# @lc code=start
class Solution {
    private static final int MOD = 1_000_000_007;

    public int[] assignEdgeWeights(int[][] edges, int[][] queries) {
        int n = edges.length + 1;
        List<Integer>[] tree = new ArrayList[n + 1];
        for (int i = 1; i <= n; i++) tree[i] = new ArrayList<>();
        for (int[] e : edges) {
            tree[e[0]].add(e[1]);
            tree[e[1]].add(e[0]);
        }
        int LOG = 17;
        int[][] parent = new int[n + 1][LOG];
        int[] depth = new int[n + 1];
        dfs(tree, 1, 0, depth, parent, LOG);
        // Binary lifting
        for (int k = 1; k < LOG; k++) {
            for (int v = 1; v <= n; v++) {
                if (parent[v][k - 1] != 0)
                    parent[v][k] = parent[parent[v][k - 1]][k - 1];
            }
        }
        int[] ans = new int[queries.length];
        for (int i = 0; i < queries.length; i++) {
            int u = queries[i][0], v = queries[i][1];
            if (u == v) {
                ans[i] = 0;
                continue;
            }
            int lca = getLCA(u, v, depth, parent, LOG);
            int k = depth[u] + depth[v] - 2 * depth[lca];
            // Verification step: ensure k is non-negative
            if (k < 0) k = 0;
            if (k == 0) ans[i] = 0;
            else ans[i] = modPow(2, k - 1, MOD);
        }
        return ans;
    }
    private void dfs(List<Integer>[] tree, int u, int p, int[] depth, int[][] parent, int LOG) {
        parent[u][0] = p;
        for (int v : tree[u]) {
            if (v != p) {
                depth[v] = depth[u] + 1;
                dfs(tree, v, u, depth, parent, LOG);
            }
        }
    }
    private int getLCA(int u, int v, int[] depth, int[][] parent, int LOG) {
        if (depth[u] < depth[v]) { int t = u; u = v; v = t; }
        for (int k = LOG - 1; k >= 0; k--) {
            if (depth[u] - (1 << k) >= depth[v]) {
                u = parent[u][k];
            }
        }
        if (u == v) return u;
        for (int k = LOG - 1; k >= 0; k--) {
            if (parent[u][k] != 0 && parent[u][k] != parent[v][k]) {
                u = parent[u][k];
                v = parent[v][k];
            }
        }
        return parent[u][0];
    }
    private int modPow(int a, int b, int mod) {
        long ans = 1, base = a;
        while (b > 0) {
            if ((b & 1) == 1) ans = (ans * base) % mod;
            base = (base * base) % mod;
            b >>= 1;
        }
        return (int) ans;
    }
}
# @lc code=end