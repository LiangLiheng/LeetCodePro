#
# @lc app=leetcode id=3462 lang=java
#
# [3462] Maximum Sum With at Most K Elements
#
# @lc code=start
class Solution {
    public long maxSum(int[][] grid, int[] limits, int k) {
        int n = grid.length, m = grid[0].length;
        long[] dp = new long[k + 1];
        for (int i = 0; i < n; i++) {
            int[] row = grid[i];
            Arrays.sort(row);
            int lim = limits[i];
            int take = Math.min(lim, row.length);
            long[] prefix = new long[take + 1];
            for (int j = 1; j <= take; j++) {
                prefix[j] = prefix[j - 1] + row[row.length - j];
            }
            long[] ndp = dp.clone();
            for (int cnt = 0; cnt <= take; cnt++) {
                for (int j = k; j >= cnt; j--) {
                    ndp[j] = Math.max(ndp[j], dp[j - cnt] + prefix[cnt]);
                }
            }
            dp = ndp;
        }
        long ans = 0;
        for (int i = 0; i <= k; i++) ans = Math.max(ans, dp[i]);
        return ans;
    }
}
# @lc code=end