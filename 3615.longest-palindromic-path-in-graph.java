#
# @lc app=leetcode id=3615 lang=java
#
# [3615] Longest Palindromic Path in Graph
#

# @lc code=start
class Solution {
    public int maxLen(int n, int[][] edges, String label) {
        java.util.List<java.lang.Integer>[] adj = new java.util.ArrayList[n];
        for (int i = 0; i < n; i++) {
            adj[i] = new java.util.ArrayList<>();
        }
        for (int[] e : edges) {
            adj[e[0]].add(e[1]);
            adj[e[1]].add(e[0]);
        }
        int N = 1 << n;
        boolean[][][] dp = new boolean[N][n][n];
        int ans = 1;
        // length 1
        for (int i = 0; i < n; i++) {
            dp[1 << i][i][i] = true;
        }
        // length 2
        for (int u = 0; u < n; u++) {
            for (int v : adj[u]) {
                if (label.charAt(u) == label.charAt(v)) {
                    int msk = (1 << u) | (1 << v);
                    dp[msk][u][v] = true;
                    dp[msk][v][u] = true;
                    ans = Math.max(ans, 2);
                }
            }
        }
        // longer paths
        for (int mask = 0; mask < N; mask++) {
            int pc = Integer.bitCount(mask);
            if (pc < 3) continue;
            for (int u = 0; u < n; u++) {
                if ((mask & (1 << u)) == 0) continue;
                for (int v = 0; v < n; v++) {
                    if (v == u || (mask & (1 << v)) == 0) continue;
                    if (label.charAt(u) != label.charAt(v)) continue;
                    int inner = mask ^ (1 << u) ^ (1 << v);
                    boolean can = false;
                    for (int xi = 0; xi < adj[u].size() && !can; xi++) {
                        int x = adj[u].get(xi);
                        if ((inner & (1 << x)) == 0) continue;
                        for (int yi = 0; yi < adj[v].size() && !can; yi++) {
                            int y = adj[v].get(yi);
                            if ((inner & (1 << y)) == 0) continue;
                            if (dp[inner][x][y]) {
                                can = true;
                            }
                        }
                    }
                    dp[mask][u][v] = can;
                    dp[mask][v][u] = can;
                    if (can) {
                        ans = Math.max(ans, pc);
                    }
                }
            }
        }
        return ans;
    }
}
# @lc code=end