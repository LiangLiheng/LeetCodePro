#
# @lc app=leetcode id=3310 lang=java
#
# [3310] Remove Methods From Project
#
# @lc code=start
import java.util.*;
class Solution {
    public List<Integer> remainingMethods(int n, int k, int[][] invocations) {
        // Build the invocation graph: who invokes whom
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] inv : invocations) {
            int a = inv[0], b = inv[1];
            graph.get(a).add(b);
        }
        // Find all suspicious methods via BFS from k
        boolean[] suspicious = new boolean[n];
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(k);
        suspicious[k] = true;
        while (!queue.isEmpty()) {
            int curr = queue.poll();
            for (int nei : graph.get(curr)) {
                if (!suspicious[nei]) {
                    suspicious[nei] = true;
                    queue.offer(nei);
                }
            }
        }
        // Check if any method outside suspicious invokes into suspicious
        for (int i = 0; i < n; i++) {
            if (!suspicious[i]) {
                for (int nei : graph.get(i)) {
                    if (suspicious[nei]) {
                        // Not allowed to remove
                        List<Integer> all = new ArrayList<>();
                        for (int j = 0; j < n; j++) all.add(j);
                        return all;
                    }
                }
            }
        }
        // Safe to remove all suspicious methods
        List<Integer> res = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            if (!suspicious[i]) res.add(i);
        }
        return res;
    }
}
# @lc code=end