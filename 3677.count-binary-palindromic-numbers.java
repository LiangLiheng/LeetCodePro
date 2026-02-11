#
# @lc app=leetcode id=3677 lang=java
#
# [3677] Count Binary Palindromic Numbers
#

# @lc code=start
class Solution {
    public int countBinaryPalindromes(long n) {
        if (n == 0) {
            return 1;
        }
        String s = Long.toBinaryString(n);
        int L = s.length();
        long cnt = 1L;
        for (int len = 1; len < L; ++len) {
            int half = (len + 1) / 2;
            cnt += 1L << (half - 1);
        }
        int left_len = (L + 1) / 2;
        long[][] dp = new long[left_len + 1][2];
        int rh_len = L / 2;
        long mirror_val = 1;
        for (int j = 0; j < rh_len; ++j) {
            int fbit = s.charAt(rh_len - 1 - j) - '0';
            int sbit = s.charAt(left_len + j) - '0';
            if (fbit > sbit) {
                mirror_val = 0;
                break;
            } else if (fbit < sbit) {
                break;
            }
        }
        dp[left_len][0] = 1;
        dp[left_len][1] = mirror_val;
        for (int pos = left_len - 1; pos >= 0; --pos) {
            // tight = 0
            {
                long ways = 0;
                int up = 1;
                int low = (pos == 0 ? 1 : 0);
                for (int d = low; d <= up; ++d) {
                    ways += dp[pos + 1][0];
                }
                dp[pos][0] = ways;
            }
            // tight = 1
            {
                long ways = 0;
                int up = s.charAt(pos) - '0';
                int low = (pos == 0 ? 1 : 0);
                for (int d = low; d <= up; ++d) {
                    int nt = (d == up ? 1 : 0);
                    ways += dp[pos + 1][nt];
                }
                dp[pos][1] = ways;
            }
        }
        cnt += dp[0][1];
        return (int) cnt;
    }
}
# @lc code=end