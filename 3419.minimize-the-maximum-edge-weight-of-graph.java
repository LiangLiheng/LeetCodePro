#
# @lc app=leetcode id=3419 lang=java
#
# [3419] Minimize the Maximum Edge Weight of Graph
#
# @lc code=start
import java.util.*;
class Solution {
    public int minMaxWeight(int n, int[][] edges, int threshold) {
        int left = 1, right = 0;
        for (int[] e : edges) right = Math.max(right, e[2]);
        int res = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (isValid(n, edges, threshold, mid)) {
                res = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return res;
    }
    private boolean isValid(int n, int[][] edges, int threshold, int maxW) {
        List<List<int[]>> g = new ArrayList<>();
        for (int i = 0; i < n; ++i) g.add(new ArrayList<>());
        Map<Integer, PriorityQueue<int[]>> pqMap = new HashMap<>();
        for (int[] e : edges) {
            if (e[2] <= maxW) {
                pqMap.computeIfAbsent(e[0], k -> new PriorityQueue<>(Comparator.comparingInt(a -> a[2]))).add(e);
            }
        }
        for (int i = 0; i < n; ++i) {
            PriorityQueue<int[]> pq = pqMap.getOrDefault(i, new PriorityQueue<>());
            List<int[]> out = new ArrayList<>();
            for (int j = 0; j < threshold && !pq.isEmpty(); ++j) {
                out.add(pq.poll());
            }
            g.get(i).addAll(out);
        }
        // Verification: Confirm each node's outgoing edge count does not exceed threshold and all edge weights <= maxW
        for (int i = 0; i < n; ++i) {
            if (g.get(i).size() > threshold) return false;
            for (int[] e : g.get(i)) {
                if (e[2] > maxW) return false;
            }
        }
        // Reverse the graph
        List<List<Integer>> rg = new ArrayList<>();
        for (int i = 0; i < n; ++i) rg.add(new ArrayList<>());
        for (int u = 0; u < n; ++u) {
            for (int[] e : g.get(u)) {
                int v = e[1];
                rg.get(v).add(u);
            }
        }
        // BFS from node 0 in reversed graph
        boolean[] seen = new boolean[n];
        Queue<Integer> q = new LinkedList<>();
        q.add(0); seen[0] = true;
        while (!q.isEmpty()) {
            int u = q.poll();
            for (int v : rg.get(u)) {
                if (!seen[v]) {
                    seen[v] = true;
                    q.add(v);
                }
            }
        }
        for (boolean b : seen) if (!b) return false;
        return true;
    }
}
# @lc code=end