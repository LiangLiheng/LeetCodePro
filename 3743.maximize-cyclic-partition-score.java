#
# @lc app=leetcode id=3743 lang=java
#
# [3743] Maximize Cyclic Partition Score
#

# @lc code=start
class Solution {
    public long maximumScore(int[] nums, int k) {
        int n = nums.length;
        long res = 0;
        // Try all possible starts due to cyclic property
        for (int shift = 0; shift < n; ++shift) {
            // Linearize the array for this rotation
            int[] arr = new int[n];
            for (int i = 0; i < n; ++i) {
                arr[i] = nums[(shift + i) % n];
            }
            // Precompute range (max - min) for all subarrays
            long[][] range = new long[n][n];
            for (int i = 0; i < n; ++i) {
                int max = arr[i], min = arr[i];
                for (int j = i; j < n; ++j) {
                    max = Math.max(max, arr[j]);
                    min = Math.min(min, arr[j]);
                    range[i][j] = max - min;
                }
            }
            // DP: dp[i][p] = max score for first i elements using p partitions
            int K = k;
            long[][] dp = new long[n + 1][K + 1];
            for (int i = 0; i <= n; ++i)
                for (int j = 0; j <= K; ++j)
                    dp[i][j] = Long.MIN_VALUE;
            dp[0][0] = 0;
            for (int i = 1; i <= n; ++i) {
                for (int p = 1; p <= Math.min(i, K); ++p) {
                    for (int j = p - 1; j < i; ++j) {
                        if (dp[j][p - 1] != Long.MIN_VALUE) {
                            dp[i][p] = Math.max(dp[i][p], dp[j][p - 1] + range[j][i - 1]);
                        }
                    }
                }
            }
            // For this rotation, get the best score using up to k partitions
            for (int p = 1; p <= K; ++p) {
                res = Math.max(res, dp[n][p]);
            }
        }
        return res;
    }
}
# @lc code=end