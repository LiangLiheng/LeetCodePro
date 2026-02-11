#
# @lc app=leetcode id=3530 lang=java
#
# [3530] Maximum Profit from Valid Topological Order in DAG
#

# @lc code=start
class Solution {
  public int maxProfit(int n, int[][] edges, int[] score) {
    int[] predmask = new int[n];
    for (int[] edge : edges) {
      predmask[edge[1]] |= (1 << edge[0]);
    }
    int N = 1 << n;
    int[] dp = new int[N];
    for (int i = 0; i < N; i++) {
      dp[i] = Integer.MIN_VALUE / 2;
    }
    dp[0] = 0;
    for (int mask = 0; mask < N; mask++) {
      if (dp[mask] < 0) continue;
      int pos = Integer.bitCount(mask) + 1;
      for (int u = 0; u < n; u++) {
        if (((mask & (1 << u)) == 0) && ((predmask[u] & mask) == predmask[u])) {
          int nmask = mask | (1 << u);
          dp[nmask] = Math.max(dp[nmask], dp[mask] + score[u] * pos);
        }
      }
    }
    return dp[N - 1];
  }
}
# @lc code=end