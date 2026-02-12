#
# @lc app=leetcode id=3519 lang=java
#
# [3519] Count Numbers with Non-Decreasing Digits
#

# @lc code=start
class Solution {
    static final int MOD = 1000000007;
    
    public int countNumbers(String l, String r, int b) {
        int[] rDigits = toBaseB(r, b);
        int[] lDigits = toBaseB(l, b);
        int countR = countNonDecreasing(rDigits, b);
        int[] lMinus1 = subtractOne(lDigits, b);
        int countL = countNonDecreasing(lMinus1, b);
        int ans = (countR - countL + MOD) % MOD;
        return ans;
    }
    
    // Converts a decimal string to a digit array in base b (most significant digit first)
    private int[] toBaseB(String s, int b) {
        java.util.ArrayList<Integer> digits = new java.util.ArrayList<>();
        java.math.BigInteger base = java.math.BigInteger.valueOf(b);
        java.math.BigInteger num = new java.math.BigInteger(s);
        if (num.equals(java.math.BigInteger.ZERO)) return new int[]{0};
        while (num.compareTo(java.math.BigInteger.ZERO) > 0) {
            digits.add(0, num.mod(base).intValue());
            num = num.divide(base);
        }
        int[] arr = new int[digits.size()];
        for (int i = 0; i < digits.size(); ++i) arr[i] = digits.get(i);
        return arr;
    }
    
    // Subtract one from a base-b digit array
    private int[] subtractOne(int[] digits, int b) {
        int n = digits.length;
        int[] res = digits.clone();
        int i = n - 1;
        while (i >= 0) {
            if (res[i] > 0) {
                res[i]--;
                break;
            } else {
                res[i] = b - 1;
                i--;
            }
        }
        // Remove leading zeros
        int firstNonZero = 0;
        while (firstNonZero < res.length - 1 && res[firstNonZero] == 0) firstNonZero++;
        int[] trimmed = new int[res.length - firstNonZero];
        System.arraycopy(res, firstNonZero, trimmed, 0, trimmed.length);
        return trimmed;
    }
    
    // Digit DP to count numbers with non-decreasing digits up to given digit array
    private int countNonDecreasing(int[] digits, int b) {
        int n = digits.length;
        Integer[][][][] dp = new Integer[n + 1][b][2][2];
        return dfs(0, 0, true, true, digits, b, dp);
    }
    // pos: current digit position
    // prev: previous digit selected (for leading zeros, 0 is default)
    // tight: whether prefix matches bound
    // leadingZero: whether leading zeros are still present
    private int dfs(int pos, int prev, boolean tight, boolean leadingZero, int[] digits, int b, Integer[][][][] dp) {
        if (pos == digits.length) return leadingZero ? 0 : 1;
        int tightInt = tight ? 1 : 0;
        int lzInt = leadingZero ? 1 : 0;
        if (dp[pos][prev][tightInt][lzInt] != null) return dp[pos][prev][tightInt][lzInt];
        int res = 0;
        int up = tight ? digits[pos] : b - 1;
        for (int d = 0; d <= up; ++d) {
            if (!leadingZero && d < prev) continue;
            boolean nextTight = tight && (d == up);
            boolean nextLZ = leadingZero && (d == 0);
            int nextPrev = (leadingZero && d == 0) ? 0 : d;
            res = (res + dfs(pos + 1, nextPrev, nextTight, nextLZ, digits, b, dp)) % MOD;
        }
        dp[pos][prev][tightInt][lzInt] = res;
        return res;
    }
}
# @lc code=end