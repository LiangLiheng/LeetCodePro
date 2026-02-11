#
# @lc app=leetcode id=3704 lang=java
#
# [3704] Count No-Zero Pairs That Sum to N
#

# @lc code=start
class Solution {
  public long countNoZeroPairs(long n) {
    String s = String.valueOf(n);
    int L = s.length();
    int[] digits = new int[L];
    for (int i = 0; i < L; ++i) {
      digits[i] = s.charAt(i) - '0';
    }
    long[][][][] dp = new long[L + 1][2][2][2];
    for (int sa = 0; sa < 2; ++sa) {
      for (int sb = 0; sb < 2; ++sb) {
        dp[L][sa][sb][0] = (sa == 1 && sb == 1) ? 1L : 0L;
        dp[L][sa][sb][1] = 0L;
      }
    }
    for (int pos = L - 1; pos >= 0; --pos) {
      for (int sa = 0; sa < 2; ++sa) {
        for (int sb = 0; sb < 2; ++sb) {
          long tot0 = 0L;
          long tot1 = 0L;
          int mina = sa == 1 ? 1 : 0;
          int minb = sb == 1 ? 1 : 0;
          for (int da = mina; da <= 9; ++da) {
            int nsa = sa | (da != 0 ? 1 : 0);
            for (int db = minb; db <= 9; ++db) {
              int nsb = sb | (db != 0 ? 1 : 0);
              for (int cin = 0; cin < 2; ++cin) {
                int sumv = da + db + cin;
                if (sumv % 10 == digits[pos]) {
                  int cout = sumv / 10;
                  long ways = dp[pos + 1][nsa][nsb][cin];
                  if (cout == 0) {
                    tot0 += ways;
                  } else {
                    tot1 += ways;
                  }
                }
              }
            }
          }
          dp[pos][sa][sb][0] = tot0;
          dp[pos][sa][sb][1] = tot1;
        }
      }
    }
    return dp[0][0][0][0];
  }
}
# @lc code=end