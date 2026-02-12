#
# @lc app=leetcode id=3530 lang=java
#
# [3530] Maximum Profit from Valid Topological Order in DAG
#
# @lc code=start
class Solution {
    public int maxProfit(int n, int[][] edges, int[] score) {
        int[] deps = new int[n]; // dependencies as bitmask
        for (int[] e : edges) {
            int u = e[0], v = e[1];
            deps[v] |= (1 << u);
        }
        int N = 1 << n;
        int[] dp = new int[N];
        for (int mask = 0; mask < N; ++mask) {
            int pos = Integer.bitCount(mask); // number of processed nodes
            for (int u = 0; u < n; ++u) {
                if ((mask & (1 << u)) == 0 && (deps[u] & ~mask) == 0) {
                    int newMask = mask | (1 << u);
                    dp[newMask] = Math.max(dp[newMask], dp[mask] + score[u] * (pos + 1));
                }
            }
        }
        return dp[N-1];
    }
}
# @lc code=end