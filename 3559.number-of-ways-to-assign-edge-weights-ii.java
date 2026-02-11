#
# @lc app=leetcode id=3559 lang=java
#
# [3559] Number of Ways to Assign Edge Weights II
#

# @lc code=start
class Solution {
    public int[] assignEdgeWeights(int[][] edges, int[][] queries) {
        int n = edges.length + 1;
        java.util.List<java.util.List<Integer>> adj = new java.util.ArrayList<>(n + 1);
        for (int i = 0; i <= n; i++) {
            adj.add(new java.util.ArrayList<>());
        }
        for (int[] edge : edges) {
            int a = edge[0];
            int b = edge[1];
            adj.get(a).add(b);
            adj.get(b).add(a);
        }
        final int MOD = 1000000007;
        final int LOG = 18;
        int[][] up = new int[n + 1][LOG];
        int[] dep = new int[n + 1];
        boolean[] vis = new boolean[n + 1];
        java.util.Queue<Integer> q = new java.util.LinkedList<>();
        q.offer(1);
        vis[1] = true;
        dep[1] = 0;
        up[1][0] = 1;
        while (!q.isEmpty()) {
            int u = q.poll();
            for (int v : adj.get(u)) {
                if (!vis[v]) {
                    vis[v] = true;
                    dep[v] = dep[u] + 1;
                    up[v][0] = u;
                    q.offer(v);
                }
            }
        }
        for (int j = 1; j < LOG; j++) {
            for (int i = 1; i <= n; i++) {
                int p = up[i][j - 1];
                up[i][j] = up[p][j - 1];
            }
        }
        int m = queries.length;
        int[] answer = new int[m];
        for (int i = 0; i < m; i++) {
            int x = queries[i][0];
            int y = queries[i][1];
            if (x == y) {
                answer[i] = 0;
                continue;
            }
            int u = x, v = y;
            if (dep[u] > dep[v]) {
                int tmp = u;
                u = v;
                v = tmp;
            }
            int diff = dep[v] - dep[u];
            for (int j = 0; j < LOG; j++) {
                if ((diff & (1 << j)) != 0) {
                    v = up[v][j];
                }
            }
            if (u == v) {
                int lca_dep = dep[u];
                int k = dep[x] + dep[y] - 2 * lca_dep;
                long ways = modPow(2L, k - 1L, MOD);
                answer[i] = (int) ways;
                continue;
            }
            for (int j = LOG - 1; j >= 0; j--) {
                if (up[u][j] != up[v][j]) {
                    u = up[u][j];
                    v = up[v][j];
                }
            }
            int lca = up[u][0];
            int k = dep[x] + dep[y] - 2 * dep[lca];
            long ways = modPow(2L, k - 1L, MOD);
            answer[i] = (int) ways;
        }
        return answer;
    }
    private long modPow(long base, long exp, long mod) {
        long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp % 2 == 1) {
                res = res * base % mod;
            }
            base = base * base % mod;
            exp /= 2;
        }
        return res;
    }
}
# @lc code=end