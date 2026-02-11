import java.math.BigInteger;
#
# @lc app=leetcode id=3519 lang=java
#
# [3519] Count Numbers with Non-Decreasing Digits
#
# @lc code=start
class Solution {
    private static final long MOD = 1000000007L;

    public int countNumbers(String l, String r, int b) {
        long countR = solve(r, b);
        BigInteger Lbig = new BigInteger(l);
        long countL = 0L;
        if (Lbig.compareTo(BigInteger.ZERO) > 0) {
            String lMinusOneStr = Lbig.subtract(BigInteger.ONE).toString();
            countL = solve(lMinusOneStr, b);
        }
        long result = (countR - countL + MOD) % MOD;
        return (int) result;
    }

    private long solve(String S, int b) {
        BigInteger num = new BigInteger(S);
        String baseStr = num.toString(b);
        int L = baseStr.length();
        int[] digits = new int[L];
        for (int i = 0; i < L; i++) {
            digits[i] = baseStr.charAt(i) - '0';
        }
        long[][][][] dp = new long[L + 1][b][2][2];
        for (int p = 0; p < b; p++) {
            for (int t = 0; t < 2; t++) {
                for (int z = 0; z < 2; z++) {
                    dp[L][p][t][z] = 1L;
                }
            }
        }
        for (int pos = L - 1; pos >= 0; pos--) {
            for (int prev = 0; prev < b; prev++) {
                for (int tight = 0; tight < 2; tight++) {
                    for (int leadz = 0; leadz < 2; leadz++) {
                        long res = 0L;
                        int up = tight == 1 ? digits[pos] : b - 1;
                        for (int d = 0; d <= up; d++) {
                            int newTight = (tight == 1 && d == up) ? 1 : 0;
                            int newLeadz = (leadz == 1 && d == 0) ? 1 : 0;
                            int newPrev;
                            if (newLeadz == 1) {
                                newPrev = 0;
                            } else if (leadz == 1) {
                                newPrev = d;
                            } else {
                                if (d < prev) continue;
                                newPrev = d;
                            }
                            res = (res + dp[pos + 1][newPrev][newTight][newLeadz]) % MOD;
                        }
                        dp[pos][prev][tight][leadz] = res;
                    }
                }
            }
        }
        return dp[0][0][1][1];
    }
}
# @lc code=end