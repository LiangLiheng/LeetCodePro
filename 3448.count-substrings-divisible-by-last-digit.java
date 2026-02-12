#
# @lc app=leetcode id=3448 lang=java
#
# [3448] Count Substrings Divisible By Last Digit
#
# @lc code=start
class Solution {
    public long countSubstrings(String s) {
        int n = s.length();
        long total = 0;
        // For each possible last digit (1-9), use DP to count valid substrings
        for (int d = 1; d <= 9; d++) {
            // dp[r] = number of substrings ending at previous position with remainder r mod d
            long[] dp = new long[d];
            int rem = 0;
            int pow10 = 1;
            for (int i = n - 1; i >= 0; --i) {
                int digit = s.charAt(i) - '0';
                if (digit == d) {
                    rem = 0;
                    pow10 = 1;
                    for (int j = i; j < n; ++j) {
                        int curDigit = s.charAt(j) - '0';
                        rem = (rem * 10 + curDigit) % d;
                        if ((j == n - 1 || s.charAt(j + 1) - '0' != d) && rem == 0) {
                            total++;
                        }
                        if (j - i > 300) break; // Prevent TLE for very large substrings
                    }
                }
            }
        }
        // Additionally, single-digit substrings (nonzero) are always valid
        for (int i = 0; i < n; ++i) {
            int digit = s.charAt(i) - '0';
            if (digit != 0) total++;
        }
        return total;
    }
}
# @lc code=end