#
# @lc app=leetcode id=3585 lang=java
#
# [3585] Find Weighted Median Node in Tree
#

# @lc code=start
import java.util.*;

class Solution {
    public int[] findMedian(int n, int[][] edges, int[][] queries) {
        final int LOG = 20;
        @SuppressWarnings("unchecked")
        List<int[]>[] graph = new List[n];
        for (int i = 0; i < n; i++) {
            graph[i] = new ArrayList<int[]>();
        }
        for (int[] e : edges) {
            int u = e[0], v = e[1], w = e[2];
            graph[u].add(new int[]{v, w});
            graph[v].add(new int[]{u, w});
        }
        long[] dist = new long[n];
        int[] dep = new int[n];
        int[][] par = new int[LOG][n];
        long[][] upsum = new long[LOG][n];
        boolean[] visited = new boolean[n];
        Queue<Integer> queue = new LinkedList<Integer>();
        par[0][0] = -1;
        upsum[0][0] = 0;
        dep[0] = 0;
        dist[0] = 0;
        visited[0] = true;
        queue.offer(0);
        while (!queue.isEmpty()) {
            int node = queue.poll();
            for (int[] edge : graph[node]) {
                int child = edge[0];
                if (!visited[child]) {
                    visited[child] = true;
                    par[0][child] = node;
                    upsum[0][child] = edge[1];
                    dist[child] = dist[node] + edge[1];
                    dep[child] = dep[node] + 1;
                    queue.offer(child);
                }
            }
        }
        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                int p = par[k - 1][i];
                if (p != -1) {
                    par[k][i] = par[k - 1][p];
                    upsum[k][i] = upsum[k - 1][i] + upsum[k - 1][p];
                } else {
                    par[k][i] = -1;
                    upsum[k][i] = 0;
                }
            }
        }
        int[] ans = new int[queries.length];
        for (int qi = 0; qi < queries.length; qi++) {
            int u = queries[qi][0];
            int v = queries[qi][1];
            // Compute LCA
            int a = u, b = v;
            if (dep[a] > dep[b]) {
                int tmp = a;
                a = b;
                b = tmp;
            }
            int diff = dep[b] - dep[a];
            for (int k = 0; k < LOG; k++) {
                if ((diff & (1 << k)) != 0) {
                    b = par[k][b];
                }
            }
            int lc;
            if (a == b) {
                lc = a;
            } else {
                for (int k = LOG - 1; k >= 0; k--) {
                    if (par[k][a] != -1 && par[k][b] != -1 && par[k][a] != par[k][b]) {
                        a = par[k][a];
                        b = par[k][b];
                    }
                }
                lc = par[0][a];
            }
            // Now compute median
            long total = dist[u] + dist[v] - 2L * dist[lc];
            long T = (total + 1L) / 2L;
            long pre = dist[u] - dist[lc];
            int med;
            if (pre >= T) {
                // u to lc
                long cum = 0L;
                int cur = u;
                for (int k = LOG - 1; k >= 0; k--) {
                    int nxt = par[k][cur];
                    if (nxt != -1 && dep[nxt] >= dep[lc] && cum + upsum[k][cur] < T) {
                        cum += upsum[k][cur];
                        cur = nxt;
                    }
                }
                if (cum >= T) {
                    med = cur;
                } else {
                    med = par[0][cur];
                }
            } else {
                // lc to v
                long needd = T - pre;
                long fulll = dist[v] - dist[lc];
                long maxupp = fulll - needd;
                long cumupp = 0L;
                int cur = v;
                for (int k = LOG - 1; k >= 0; k--) {
                    int nxt = par[k][cur];
                    if (nxt != -1 && dep[nxt] >= dep[lc] && cumupp + upsum[k][cur] <= maxupp) {
                        cumupp += upsum[k][cur];
                        cur = nxt;
                    }
                }
                med = cur;
            }
            ans[qi] = med;
        }
        return ans;
    }
}
# @lc code=end