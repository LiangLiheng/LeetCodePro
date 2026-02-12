#
# @lc app=leetcode id=3704 lang=java
#
# [3704] Count No-Zero Pairs That Sum to N
#
# @lc code=start
class Solution {
    public long countNoZeroPairs(long n) {
        int[] digits = getDigits(n);
        // dp[pos][carry][tight]: position, carry, tightness with n
        Long[][][] memo = new Long[digits.length + 1][2][2];
        return dfs(0, 0, 1, digits, memo);
    }

    // Extract digits from n, least to most significant (right to left)
    private int[] getDigits(long n) {
        String s = Long.toString(n);
        int[] res = new int[s.length()];
        for (int i = s.length() - 1, j = 0; i >= 0; --i, ++j) {
            res[j] = s.charAt(i) - '0';
        }
        return res;
    }

    // pos: digit position (0 = least significant)
    // carry: carry from previous sum
    // tight: if true, sum so far equals n's prefix
    private long dfs(int pos, int carry, int tight, int[] digits, Long[][][] memo) {
        if (pos == digits.length) {
            return carry == 0 ? 1 : 0;
        }
        if (memo[pos][carry][tight] != null) return memo[pos][carry][tight];
        long res = 0;
        int nDigit = digits[pos];
        int maxSum = tight == 1 ? nDigit : 18;
        for (int a = 1; a <= 9; ++a) {
            for (int b = 1; b <= 9; ++b) {
                int sum = a + b + carry;
                int curDigit = sum % 10;
                int newCarry = sum / 10;
                if (curDigit > maxSum) continue;
                if (tight == 1 && curDigit < nDigit) continue;
                if (tight == 1 && curDigit > nDigit) continue;
                int nextTight = (tight == 1 && curDigit == nDigit) ? 1 : 0;
                res += dfs(pos + 1, newCarry, nextTight, digits, memo);
            }
        }
        memo[pos][carry][tight] = res;
        return res;
    }
}
# @lc code=end