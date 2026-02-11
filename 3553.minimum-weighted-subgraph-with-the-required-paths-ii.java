#
# @lc app=leetcode id=3553 lang=java
#
# [3553] Minimum Weighted Subgraph With the Required Paths II
#

# @lc code=start
import java.util.*;
import java.util.function.BiFunction;

class Solution {
    public int[] minimumWeight(int[][] edges, int[][] queries) {
        int n = edges.length + 1;
        @SuppressWarnings("unchecked")
        List<int[]>[] adj = new List[n];
        for (int i = 0; i < n; i++) {
            adj[i] = new ArrayList<>();
        }
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            adj[u].add(new int[]{v, w});
            adj[v].add(new int[]{u, w});
        }
        long[] dist = new long[n];
        Arrays.fill(dist, -1L);
        int[] dep = new int[n];
        int[][] par = new int[n][18];
        Queue<Integer> q = new LinkedList<>();
        q.offer(0);
        dist[0] = 0;
        dep[0] = 0;
        par[0][0] = -1;
        while (!q.isEmpty()) {
            int u = q.poll();
            for (int[] pr : adj[u]) {
                int v = pr[0];
                int w = pr[1];
                if (dist[v] == -1L) {
                    dist[v] = dist[u] + w;
                    dep[v] = dep[u] + 1;
                    par[v][0] = u;
                    q.offer(v);
                }
            }
        }
        for (int k = 1; k < 18; k++) {
            for (int i = 0; i < n; i++) {
                int p = par[i][k - 1];
                par[i][k] = (p == -1 ? -1 : par[p][k - 1]);
            }
        }
        BiFunction<Integer, Integer, Integer> getLCA = (u, v) -> {
            int ua = u, va = v;
            if (dep[ua] > dep[va]) {
                int tmp = ua;
                ua = va;
                va = tmp;
            }
            int df = dep[va] - dep[ua];
            for (int k = 0; k < 18; k++) {
                if ((df & (1 << k)) != 0) {
                    va = par[va][k];
                }
            }
            if (ua == va) {
                return ua;
            }
            for (int k = 17; k >= 0; k--) {
                if (par[ua][k] != par[va][k] && par[ua][k] != -1 && par[va][k] != -1) {
                    ua = par[ua][k];
                    va = par[va][k];
                }
            }
            return par[ua][0] != -1 ? par[ua][0] : ua;
        };
        BiFunction<Integer, Integer, Long> getDist = (u, v) -> {
            int l = getLCA.apply(u, v);
            return dist[u] + dist[v] - 2L * dist[l];
        };
        int m = queries.length;
        int[] answer = new int[m];
        for (int j = 0; j < m; j++) {
            int s1 = queries[j][0];
            int s2 = queries[j][1];
            int des = queries[j][2];
            long d1d = getDist.apply(s1, des);
            long d2d = getDist.apply(s2, des);
            long d12 = getDist.apply(s1, s2);
            long dmd = (d1d + d2d - d12) / 2;
            answer[j] = (int) (d1d + d2d - dmd);
        }
        return answer;
    }
}
# @lc code=end