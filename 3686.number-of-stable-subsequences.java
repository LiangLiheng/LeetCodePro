#
# @lc app=leetcode id=3686 lang=java
#
# [3686] Number of Stable Subsequences
#
# @lc code=start
class Solution {
    public int countStableSubsequences(int[] nums) {
        final int MOD = 1000000007;
        int n = nums.length;
        // dp[parity][consecutive]: number of subsequences ending with given parity and number of consecutive
        long[][] dp = new long[2][3]; // [0]=even, [1]=odd, [1,2] consecutive
        for (int num : nums) {
            int p = num % 2;
            int q = 1 - p;
            long[] newDp0 = new long[3];
            long[] newDp1 = new long[3];
            // Start a new subsequence with this number
            if (p == 0) newDp0[1] = 1;
            else newDp1[1] = 1;
            // Extend previous subsequences
            // If previous ends with different parity, can append and k=1
            newDp0[1] = (newDp0[1] + dp[1][1] + dp[1][2]) % MOD;
            newDp1[1] = (newDp1[1] + dp[0][1] + dp[0][2]) % MOD;
            // If previous ends with same parity and k=1, can extend to k=2
            newDp0[2] = (newDp0[2] + dp[0][1]) % MOD;
            newDp1[2] = (newDp1[2] + dp[1][1]) % MOD;
            dp[0] = newDp0;
            dp[1] = newDp1;
        }
        long total = (dp[0][1] + dp[0][2] + dp[1][1] + dp[1][2]) % MOD;
        return (int)total;
    }
}
# @lc code=end