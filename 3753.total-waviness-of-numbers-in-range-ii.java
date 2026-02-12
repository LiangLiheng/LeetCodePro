#
# @lc app=leetcode id=3753 lang=java
#
# [3753] Total Waviness of Numbers in Range II
#
# @lc code=start
class Solution {
    // Helper function to compute total waviness up to a bound using digit DP
    private long wavinessUpTo(long bound) {
        char[] digits = Long.toString(bound).toCharArray();
        int n = digits.length;
        // DP[pos][tight][prev1][prev2][leading_zero][has_started]
        Long[][][][][][] dp = new Long[n+1][2][11][11][2][2];
        // prev1/prev2: -1 (10) means undefined
        return dfs(0, 1, 10, 10, 1, 0, digits, dp);
    }

    // pos: current digit position
    // tight: is this prefix still tight to the bound
    // prev1, prev2: previous two digits (0-9 or 10 for undefined)
    // leading_zero: 1 if still placing leading zeros
    // has_started: 1 if we've started placing non-leading-zero digits
    private long dfs(int pos, int tight, int prev1, int prev2, int leading_zero, int has_started, char[] digits, Long[][][][][][] dp) {
        if (pos == digits.length) {
            return 0;
        }
        if (dp[pos][tight][prev1][prev2][leading_zero][has_started] != null) {
            return dp[pos][tight][prev1][prev2][leading_zero][has_started];
        }
        long res = 0;
        int limit = tight == 1 ? digits[pos]-'0' : 9;
        for (int d = 0; d <= limit; ++d) {
            int next_tight = (tight == 1 && d == limit) ? 1 : 0;
            int next_leading_zero = (leading_zero == 1 && d == 0) ? 1 : 0;
            int next_has_started = (has_started == 1 || (d != 0 && leading_zero == 1)) ? 1 : has_started;
            int next_prev2 = prev1;
            int next_prev1 = d;
            long add = 0;
            // Only count peaks/valleys if not leading zeros and at least three digits have been placed
            if (has_started == 1 && leading_zero == 0 && pos >=2) {
                if (prev2 != 10 && prev1 !=10) {
                    if (prev1 > prev2 && prev1 > d) add = 1; // peak
                    if (prev1 < prev2 && prev1 < d) add = 1; // valley
                }
            }
            res += add + dfs(pos+1, next_tight, next_prev1, next_prev2, next_leading_zero, next_has_started, digits, dp);
        }
        dp[pos][tight][prev1][prev2][leading_zero][has_started] = res;
        return res;
    }

    public long totalWaviness(long num1, long num2) {
        if (num1 > num2) return 0;
        long ans = wavinessUpTo(num2);
        if (num1 > 1) ans -= wavinessUpTo(num1-1);
        return ans;
    }
}
# @lc code=end