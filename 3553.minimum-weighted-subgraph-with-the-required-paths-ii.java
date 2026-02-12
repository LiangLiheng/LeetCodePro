#
# @lc app=leetcode id=3553 lang=java
#
# [3553] Minimum Weighted Subgraph With the Required Paths II
#

# @lc code=start
import java.util.*;

class Solution {
    static final int LOG = 20;
    int n;
    List<int[]>[] tree;
    int[][] parent;
    int[] depth;
    long[] prefix;
    
    public int[] minimumWeight(int[][] edges, int[][] queries) {
        n = edges.length + 1;
        tree = new ArrayList[n];
        for (int i = 0; i < n; ++i) tree[i] = new ArrayList<>();
        for (int[] e : edges) {
            int u = e[0], v = e[1], w = e[2];
            tree[u].add(new int[]{v, w});
            tree[v].add(new int[]{u, w});
        }
        parent = new int[n][LOG];
        depth = new int[n];
        prefix = new long[n];
        dfs(0, -1, 0, 0);
        for (int k = 1; k < LOG; ++k) {
            for (int v = 0; v < n; ++v) {
                if (parent[v][k-1] != -1)
                    parent[v][k] = parent[parent[v][k-1]][k-1];
                else
                    parent[v][k] = -1;
            }
        }
        int[] answer = new int[queries.length];
        for (int i = 0; i < queries.length; ++i) {
            int u = queries[i][0], v = queries[i][1], d = queries[i][2];
            int lca_uv = lca(u, v);
            long sum = dist(u, d) + dist(v, d) - dist(lca_uv, d);
            answer[i] = (int)sum;
        }
        return answer;
    }
    
    void dfs(int u, int p, int d, long wsum) {
        parent[u][0] = p;
        depth[u] = d;
        prefix[u] = wsum;
        for (int[] nbr : tree[u]) {
            int v = nbr[0], w = nbr[1];
            if (v != p) {
                dfs(v, u, d+1, wsum + w);
            }
        }
    }
    
    int lca(int u, int v) {
        if (depth[u] < depth[v]) { int tmp = u; u = v; v = tmp; }
        for (int k = LOG-1; k >= 0; --k) {
            if (parent[u][k] != -1 && depth[parent[u][k]] >= depth[v])
                u = parent[u][k];
        }
        if (u == v) return u;
        for (int k = LOG-1; k >= 0; --k) {
            if (parent[u][k] != -1 && parent[u][k] != parent[v][k]) {
                u = parent[u][k];
                v = parent[v][k];
            }
        }
        return parent[u][0];
    }
    
    long dist(int u, int v) {
        int anc = lca(u, v);
        return prefix[u] + prefix[v] - 2 * prefix[anc];
    }
}
# @lc code=end