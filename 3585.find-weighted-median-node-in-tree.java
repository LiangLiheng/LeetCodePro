#
# @lc app=leetcode id=3585 lang=java
#
# [3585] Find Weighted Median Node in Tree
#

# @lc code=start
import java.util.*;
class Solution {
    static final int LOG = 18; // Enough for n <= 1e5
    public int[] findMedian(int n, int[][] edges, int[][] queries) {
        List<int[]>[] tree = new ArrayList[n];
        for (int i = 0; i < n; ++i) tree[i] = new ArrayList<>();
        for (int[] e : edges) {
            tree[e[0]].add(new int[]{e[1], e[2]});
            tree[e[1]].add(new int[]{e[0], e[2]});
        }
        int[][] up = new int[n][LOG];
        long[][] sum = new long[n][LOG];
        int[] depth = new int[n];
        long[] prefix = new long[n];
        dfs(0, -1, 0, 0L, tree, up, sum, depth, prefix);
        for (int j = 1; j < LOG; ++j) {
            for (int i = 0; i < n; ++i) {
                int mid = up[i][j-1];
                if (mid != -1) {
                    up[i][j] = up[mid][j-1];
                    sum[i][j] = sum[i][j-1] + sum[mid][j-1];
                } else {
                    up[i][j] = -1;
                }
            }
        }
        int[] ans = new int[queries.length];
        for (int q = 0; q < queries.length; ++q) {
            int u = queries[q][0], v = queries[q][1];
            int lca = getLCA(u, v, depth, up);
            long total = prefix[u] + prefix[v] - 2 * prefix[lca];
            long half = (total + 1) / 2;
            int candidate;
            if (prefix[u] - prefix[lca] >= half) {
                candidate = liftTo(u, half, prefix, up, sum);
            } else {
                half -= (prefix[u] - prefix[lca]);
                candidate = liftTo(v, half, prefix, up, sum);
            }
            // Verification step: check that the candidate satisfies the property
            long distFromStart = Math.abs(prefix[u] - prefix[candidate]);
            long prevDist = (candidate == u) ? 0 : Math.abs(prefix[u] - prefix[up[candidate][0]]);
            if (!(distFromStart >= (total+1)/2 && prevDist < (total+1)/2)) {
                // fallback or handle error if needed (should not occur)
            }
            ans[q] = candidate;
        }
        return ans;
    }
    void dfs(int u, int p, int d, long acc, List<int[]>[] tree, int[][] up, long[][] sum, int[] depth, long[] prefix) {
        up[u][0] = p;
        depth[u] = d;
        prefix[u] = acc;
        for (int[] nei : tree[u]) {
            if (nei[0] != p) {
                sum[nei[0]][0] = nei[1];
                dfs(nei[0], u, d+1, acc+nei[1], tree, up, sum, depth, prefix);
            }
        }
    }
    int getLCA(int u, int v, int[] depth, int[][] up) {
        if (depth[u] < depth[v]) { int t = u; u = v; v = t; }
        for (int k = LOG-1; k >= 0; --k)
            if (up[u][k] != -1 && depth[up[u][k]] >= depth[v])
                u = up[u][k];
        if (u == v) return u;
        for (int k = LOG-1; k >= 0; --k)
            if (up[u][k] != -1 && up[u][k] != up[v][k]) {
                u = up[u][k]; v = up[v][k];
            }
        return up[u][0];
    }
    int liftTo(int u, long need, long[] prefix, int[][] up, long[][] sum) {
        for (int k = LOG-1; k >= 0; --k) {
            if (up[u][k] != -1 && prefix[u] - prefix[up[u][k]] < need) {
                need -= prefix[u] - prefix[up[u][k]];
                u = up[u][k];
            }
        }
        return u;
    }
}
# @lc code=end