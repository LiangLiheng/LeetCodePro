#
# @lc app=leetcode id=3544 lang=java
#
# [3544] Subtree Inversion Sum
#

# @lc code=start
import java.util.*;

class Solution {
    public long subtreeInversionSum(int[][] edges, int[] nums, int k) {
        int n = nums.length;
        List<Integer>[] adj = new List[n];
        for (int i = 0; i < n; i++) {
            adj[i] = new ArrayList<>();
        }
        for (int[] e : edges) {
            int u = e[0], v = e[1];
            adj[u].add(v);
            adj[v].add(u);
        }
        long[][][] dp = new long[n][k + 1][2];
        dfs(0, -1, adj, nums, k, dp);
        return dp[0][k][0];
    }

    private static void dfs(int u, int p, List<Integer>[] adj, int[] nums, int k, long[][][] dp) {
        List<Integer> childs = new ArrayList<>();
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, adj, nums, k, dp);
                childs.add(v);
            }
        }
        for (int d = 0; d <= k; d++) {
            int dchild = Math.min(d + 1, k);
            long sum_max_c = 0;
            long sum_min_c = 0;
            for (int c : childs) {
                sum_max_c += dp[c][dchild][0];
                sum_min_c += dp[c][dchild][1];
            }
            long opt0_max = (long) nums[u] + sum_max_c;
            long opt0_min = (long) nums[u] + sum_min_c;
            dp[u][d][0] = opt0_max;
            dp[u][d][1] = opt0_min;
            if (d == k) {
                long sum_min_c_opt1 = 0;
                long sum_max_c_opt1 = 0;
                for (int c : childs) {
                    sum_min_c_opt1 += dp[c][1][1];
                    sum_max_c_opt1 += dp[c][1][0];
                }
                long opt1_max = -((long) nums[u] + sum_min_c_opt1);
                long opt1_min = -((long) nums[u] + sum_max_c_opt1);
                dp[u][d][0] = Math.max(dp[u][d][0], opt1_max);
                dp[u][d][1] = Math.min(dp[u][d][1], opt1_min);
            }
        }
    }
}
# @lc code=end