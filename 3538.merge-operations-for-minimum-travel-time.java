#
# @lc app=leetcode id=3538 lang=java
#
# [3538] Merge Operations for Minimum Travel Time
#

# @lc code=start
class Solution {
    public int minTravelTime(int l, int n, int k, int[] position, int[] time) {
        final int INF = 2000000000;
        final int MAX_E = 101;
        int[][][] dp = new int[n][k + 1][MAX_E];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= k; j++) {
                for (int e = 0; e < MAX_E; e++) {
                    dp[i][j][e] = INF;
                }
            }
        }
        dp[0][0][0] = 0;
        int[] prefix = new int[n + 1];
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + time[i];
        }
        for (int i = 1; i < n; i++) {
            for (int p = 0; p < i; p++) {
                int num_rem = i - p - 1;
                for (int m = 0; m <= k && m + num_rem <= k; m++) {
                    for (int e = 0; e < MAX_E; e++) {
                        if (dp[p][m][e] == INF) continue;
                        int dist = position[i] - position[p];
                        long eff_time = (long) time[p] + e;
                        long seg_cost = (long) dist * eff_time;
                        int sum_rem = prefix[i] - prefix[p + 1];
                        int new_e = sum_rem;
                        if (new_e >= MAX_E) continue;
                        int new_m = m + num_rem;
                        long total_cost = (long) dp[p][m][e] + seg_cost;
                        if (total_cost < dp[i][new_m][new_e]) {
                            dp[i][new_m][new_e] = (int) total_cost;
                        }
                    }
                }
            }
        }
        int ans = INF;
        for (int e = 0; e < MAX_E; e++) {
            ans = Math.min(ans, dp[n - 1][k][e]);
        }
        return ans;
    }
}
# @lc code=end