#
# @lc app=leetcode id=3725 lang=java
#
# [3725] Count Ways to Choose Coprime Integers from Rows
#

# @lc code=start
class Solution {
    public int countCoprime(int[][] mat) {
        final int MOD = 1000000007;
        final int MAXV = 150;
        int[] mu = new int[MAXV + 1];
        boolean[] is_composite = new boolean[MAXV + 1];
        int[] primes = new int[MAXV + 1];
        int pc = 0;
        mu[1] = 1;
        for (int i = 2; i <= MAXV; i++) {
            if (!is_composite[i]) {
                primes[pc++] = i;
                mu[i] = -1;
            }
            for (int j = 0; j < pc; j++) {
                int p = primes[j];
                if ((long) i * p > MAXV) break;
                is_composite[i * p] = true;
                if (i % p == 0) {
                    mu[i * p] = 0;
                    break;
                } else {
                    mu[i * p] = -mu[i];
                }
            }
        }
        int m = mat.length;
        long ans = 0;
        for (int d = 1; d <= MAXV; d++) {
            if (mu[d] == 0) continue;
            long ways = 1;
            for (int i = 0; i < m; i++) {
                int cnt = 0;
                for (int num : mat[i]) {
                    if (num % d == 0) cnt++;
                }
                ways = ways * cnt % MOD;
            }
            if (mu[d] == 1) {
                ans = (ans + ways) % MOD;
            } else {
                ans = (ans - ways + MOD) % MOD;
            }
        }
        return (int) ans;
    }
}
# @lc code=end