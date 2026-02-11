#
# @lc app=leetcode id=3757 lang=java
#
# [3757] Number of Effective Subsequences
#

# @lc code=start
class Solution {
  public int countEffective(int[] nums) {
    int n = nums.length;
    final int K = 20;
    final int MAX = 1 << K;
    int[] dp = new int[MAX];
    int full_or = 0;
    for (int x : nums) {
      dp[x]++;
      full_or |= x;
    }
    // SOS DP: dp[S] = sum freq[T] for T subset S
    for (int b = 0; b < K; b++) {
      for (int mask = 0; mask < MAX; mask++) {
        if ((mask & (1 << b)) == 0) {
          dp[mask | (1 << b)] += dp[mask];
        }
      }
    }
    final long MOD = 1000000007L;
    long[] pow2 = new long[n + 1];
    pow2[0] = 1;
    for (int i = 1; i <= n; i++) {
      pow2[i] = pow2[i - 1] * 2 % MOD;
    }
    long ans = 0;
    for (int m = full_or; m > 0; m = (m - 1) & full_or) {
      int pop = Integer.bitCount(m);
      long sign = (pop & 1) == 1 ? 1L : (MOD - 1);
      int comp = (MAX - 1) ^ m;
      int num_zero = dp[comp];
      int cnt = n - num_zero;
      long ways = pow2[n - cnt];
      ans = (ans + sign * ways % MOD) % MOD;
    }
    return (int) ans;
  }
}
# @lc code=end