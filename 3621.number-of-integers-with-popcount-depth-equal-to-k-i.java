#
# @lc app=leetcode id=3621 lang=java
#
# [3621] Number of Integers With Popcount-Depth Equal to K I
#

# @lc code=start
class Solution {
    public long popcountDepth(long n, int k) {
        if (k == 0) {
            return 1L;
        }
        java.util.Set<Integer> targets = new java.util.HashSet<>();
        for (int m = 1; m <= 64; m++) {
            if (getDepth(m) == k - 1) {
                targets.add(m);
            }
        }
        long ans = 0L;
        for (int p : targets) {
            ans += countOnes(n, p);
        }
        if (k == 1) {
            ans -= 1L;
        }
        return ans;
    }

    private int getDepth(int x) {
        int d = 0;
        while (x > 1) {
            x = Integer.bitCount(x);
            d++;
        }
        return d;
    }

    private long countOnes(long n, int pc) {
        if (pc == 0) {
            return 0L;
        }
        String s = Long.toBinaryString(n);
        int len = s.length();
        int[] bits = new int[len];
        for (int i = 0; i < len; i++) {
            bits[i] = s.charAt(i) - '0';
        }
        long[][][] dp = new long[len + 1][2][pc + 1];
        for (int t = 0; t < 2; t++) {
            for (int o = 0; o <= pc; o++) {
                dp[len][t][o] = (o == pc ? 1L : 0L);
            }
        }
        for (int pos = len - 1; pos >= 0; pos--) {
            for (int t = 0; t < 2; t++) {
                for (int o = 0; o <= pc; o++) {
                    int up = t == 1 ? bits[pos] : 1;
                    long ways = 0L;
                    for (int d = 0; d <= up; d++) {
                        int nt = (t == 1 && d == up) ? 1 : 0;
                        int no = o + d;
                        if (no <= pc) {
                            ways += dp[pos + 1][nt][no];
                        }
                    }
                    dp[pos][t][o] = ways;
                }
            }
        }
        return dp[0][1][0];
    }
}
# @lc code=end