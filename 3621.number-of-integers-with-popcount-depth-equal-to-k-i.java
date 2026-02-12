#
# @lc app=leetcode id=3621 lang=java
#
# [3621] Number of Integers With Popcount-Depth Equal to K I
#

# @lc code=start
class Solution {
    // Memoization for popcount-depth
    private int[] depth = new int[65];
    private boolean[] computed = new boolean[65];
    
    private int popcount(int x) {
        int res = 0;
        while (x > 0) {
            res += x & 1;
            x >>= 1;
        }
        return res;
    }
    
    private int getDepth(int x) {
        if (x < 1) return -1;
        if (x == 1) return 0;
        if (computed[x]) return depth[x];
        depth[x] = 1 + getDepth(popcount(x));
        computed[x] = true;
        return depth[x];
    }
    
    // Digit DP: count numbers <= n with exactly k set bits
    private long countWithKSetBits(long n, int k) {
        int[] bits = new int[65];
        int len = 0;
        long tmp = n;
        while (tmp > 0) {
            bits[len++] = (int)(tmp & 1);
            tmp >>= 1;
        }
        // dp[pos][cnt][tight], tight: 1 if prefix matches n, 0 if already less
        Long[][][] dp = new Long[len + 1][k + 2][2];
        return dfs(bits, len - 1, k, 1, dp);
    }
    
    private long dfs(int[] bits, int pos, int k, int tight, Long[][][] dp) {
        if (k < 0) return 0;
        if (pos < 0) return k == 0 ? 1 : 0;
        if (dp[pos][k][tight] != null) return dp[pos][k][tight];
        long res = 0;
        int limit = tight == 1 ? bits[pos] : 1;
        for (int d = 0; d <= limit; ++d) {
            int newTight = (tight == 1 && d == limit) ? 1 : 0;
            res += dfs(bits, pos - 1, k - d, newTight, dp);
        }
        dp[pos][k][tight] = res;
        return res;
    }
    
    public long popcountDepth(long n, int k) {
        if (k == 0) return 0;
        computed[1] = true; depth[1] = 0;
        for (int s = 1; s <= 60; ++s) getDepth(s);
        long ans = 0;
        for (int s = 1; s <= 60; ++s) {
            if (getDepth(s) == k) {
                long cnt = countWithKSetBits(n, s);
                // Exclude 0 if counted (since [1, n])
                if (s == 1 && k == 1) cnt--;
                ans += cnt;
            }
        }
        return ans;
    }
}
# @lc code=end