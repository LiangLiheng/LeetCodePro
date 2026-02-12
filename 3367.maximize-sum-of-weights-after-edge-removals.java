#
# @lc app=leetcode id=3367 lang=java
#
# [3367] Maximize Sum of Weights after Edge Removals
#
# @lc code=start
import java.util.*;
class Solution {
    public long maximizeSumOfWeights(int[][] edges, int k) {
        int n = edges.length + 1;
        List<int[]>[] tree = new ArrayList[n];
        for (int i = 0; i < n; ++i) tree[i] = new ArrayList<>();
        for (int[] e : edges) {
            tree[e[0]].add(new int[]{e[1], e[2]});
            tree[e[1]].add(new int[]{e[0], e[2]});
        }
        return dfs(0, -1, tree, k)[0];
    }
    // returns {maxSum, sum of best k children} for subtree rooted at u
    private long[] dfs(int u, int parent, List<int[]>[] tree, int k) {
        PriorityQueue<Long> childGains = new PriorityQueue<>(); // min-heap
        long sum = 0;
        for (int[] nei : tree[u]) {
            int v = nei[0], w = nei[1];
            if (v == parent) continue;
            long[] res = dfs(v, u, tree, k);
            long gain = res[1] + w;
            childGains.offer(gain);
            sum += gain;
            if (childGains.size() > k) {
                sum -= childGains.poll();
            }
        }
        // The sum represents the maximum sum for this subtree with at most k edges from u
        return new long[]{sum, sum};
    }
}
# @lc code=end