#
# @lc app=leetcode id=3604 lang=java
#
# [3604] Minimum Time to Reach Destination in Directed Graph
#

# @lc code=start
import java.util.*;
class Solution {
    public int minTime(int n, int[][] edges) {
        List<List<int[]>> adj = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            adj.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int start = edge[2];
            int endd = edge[3];
            adj.get(u).add(new int[]{v, start, endd});
        }
        long[] dist = new long[n];
        long INF = 1L << 60;
        Arrays.fill(dist, INF);
        dist[0] = 0;
        PriorityQueue<long[]> pq = new PriorityQueue<>((a, b) -> Long.compare(a[0], b[0]));
        pq.offer(new long[]{0, 0});
        while (!pq.isEmpty()) {
            long[] p = pq.poll();
            long t = p[0];
            int u = (int) p[1];
            if (t > dist[u]) continue;
            for (int[] e : adj.get(u)) {
                int v = e[0];
                int s = e[1];
                int ee = e[2];
                long dep = Math.max(t, (long) s);
                if (dep <= ee) {
                    long nt = dep + 1;
                    if (nt < dist[v]) {
                        dist[v] = nt;
                        pq.offer(new long[]{nt, v});
                    }
                }
            }
        }
        long ans = dist[n - 1];
        return ans == INF ? -1 : (int) ans;
    }
}
# @lc code=end