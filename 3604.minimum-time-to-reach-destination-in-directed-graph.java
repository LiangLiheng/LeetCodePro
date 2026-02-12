#
# @lc app=leetcode id=3604 lang=java
#
# [3604] Minimum Time to Reach Destination in Directed Graph
#
# @lc code=start
import java.util.*;
class Solution {
    public int minTime(int n, int[][] edges) {
        // Step 1: Build adjacency list
        List<int[]>[] graph = new ArrayList[n];
        for (int i = 0; i < n; i++) graph[i] = new ArrayList<>();
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1], s = edge[2], e = edge[3];
            graph[u].add(new int[]{v, s, e});
        }
        // Step 2: Min-heap for (time, node)
        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));
        pq.offer(new int[]{0, 0}); // {currentTime, node}
        // Step 4: Track visited (node, time) pairs
        Set<Long> visited = new HashSet<>();
        while (!pq.isEmpty()) {
            int[] curr = pq.poll();
            int time = curr[0], node = curr[1];
            long state = ((long)node << 32) | time;
            if (!visited.add(state)) continue;
            if (node == n - 1) return time;
            // Step 3a: Try all outgoing edges
            for (int[] edge : graph[node]) {
                int nei = edge[0], start = edge[1], end = edge[2];
                int depart = Math.max(time, start);
                if (depart <= end) {
                    int arrive = depart + 1;
                    long nextState = ((long)nei << 32) | arrive;
                    if (!visited.contains(nextState)) {
                        pq.offer(new int[]{arrive, nei});
                    }
                }
            }
            // Step 3b: Try waiting at current node
            long waitState = ((long)node << 32) | (time + 1);
            if (!visited.contains(waitState)) {
                pq.offer(new int[]{time + 1, node});
            }
        }
        return -1;
    }
}
# @lc code=end