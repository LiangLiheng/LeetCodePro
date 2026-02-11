#
# @lc app=leetcode id=3670 lang=java
#
# [3670] Maximum Product of Two Integers With No Common Bits
#

# @lc code=start
class Solution {
    public long maxProduct(int[] nums) {
        final int BITS = 20;
        final int MAXM = 1 << BITS;
        final int MASK = MAXM - 1;
        boolean[] has = new boolean[MAXM];
        for (int x : nums) {
            if (x < MAXM) {
                has[x] = true;
            }
        }
        long[] dp = new long[MAXM];
        for (int i = 0; i < MAXM; i++) {
            dp[i] = has[i] ? i : 0L;
        }
        for (int b = 0; b < BITS; b++) {
            for (int m = 0; m < MAXM; m++) {
                if ((m & (1 << b)) == 0) {
                    int sup = m | (1 << b);
                    dp[sup] = Math.max(dp[sup], dp[m]);
                }
            }
        }
        long ans = 0;
        for (int w : nums) {
            int comp = (~w) & MASK;
            long v = dp[comp];
            ans = Math.max(ans, v * (long) w);
        }
        return ans;
    }
}
# @lc code=end