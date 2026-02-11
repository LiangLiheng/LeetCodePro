#
# @lc app=leetcode id=3686 lang=java
#
# [3686] Number of Stable Subsequences
#

# @lc code=start
class Solution {
    public int countStableSubsequences(int[] nums) {
        long MOD = 1000000007L;
        long dp10 = 0L, dp20 = 0L, dp11 = 0L, dp21 = 0L;
        for (int num : nums) {
            int cur = num % 2;
            long ndp10 = dp10;
            long ndp20 = dp20;
            long ndp11 = dp11;
            long ndp21 = dp21;
            // new single
            if (cur == 0) {
                ndp10 = (ndp10 + 1) % MOD;
            } else {
                ndp11 = (ndp11 + 1) % MOD;
            }
            // append to diff parity
            long sumDiff = (cur == 0 ? (dp11 + dp21) % MOD : (dp10 + dp20) % MOD);
            if (cur == 0) {
                ndp10 = (ndp10 + sumDiff) % MOD;
            } else {
                ndp11 = (ndp11 + sumDiff) % MOD;
            }
            // append to same streak 1
            long same1 = (cur == 0 ? dp10 : dp11);
            if (cur == 0) {
                ndp20 = (ndp20 + same1) % MOD;
            } else {
                ndp21 = (ndp21 + same1) % MOD;
            }
            dp10 = ndp10;
            dp20 = ndp20;
            dp11 = ndp11;
            dp21 = ndp21;
        }
        return (int) ((dp10 + dp20 + dp11 + dp21) % MOD);
    }
}
# @lc code=end