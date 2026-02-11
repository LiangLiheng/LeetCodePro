#
# @lc app=leetcode id=3594 lang=java
#
# [3594] Minimum Time to Transport All Individuals
#

# @lc code=start
class Solution {
    public double minTime(int n, int k, int m, int[] time, double[] mul) {
        final int FULL = (1 << n) - 1;
        final int MAX_MASK = 1 << n;
        int[] maxT = new int[MAX_MASK];
        for (int mask = 0; mask < MAX_MASK; ++mask) {
            for (int i = 0; i < n; ++i) {
                if ((mask & (1 << i)) != 0) {
                    maxT[mask] = Math.max(maxT[mask], time[i]);
                }
            }
        }
        final double INF = 1e18;
        double[][][] memo = new double[MAX_MASK][2][m];
        for (int i = 0; i < MAX_MASK; ++i) {
            for (int p = 0; p < 2; ++p) {
                for (int s = 0; s < m; ++s) {
                    memo[i][p][s] = -1.0;
                }
            }
        }
        class DfsHelper {
            double dfs(int mask, int pos, int stage) {
                if (mask == FULL) {
                    return 0.0;
                }
                if (memo[mask][pos][stage] >= 0.0) {
                    return memo[mask][pos][stage];
                }
                if (memo[mask][pos][stage] == -2.0) {
                    return INF;
                }
                memo[mask][pos][stage] = -2.0;
                double ans = INF;
                if (pos == 0) {
                    int smask = FULL ^ mask;
                    for (int g = smask; g > 0; g = (g - 1) & smask) {
                        if (Integer.bitCount(g) > k) continue;
                        double d = maxT[g] * mul[stage];
                        int adv = (int) Math.floor(d) % m;
                        int nstage = (stage + adv) % m;
                        int nmask = mask | g;
                        ans = Math.min(ans, d + dfs(nmask, 1, nstage));
                    }
                } else {
                    for (int i = 0; i < n; ++i) {
                        if ((mask & (1 << i)) != 0) {
                            double rt = time[i] * mul[stage];
                            int adv = (int) Math.floor(rt) % m;
                            int nstage = (stage + adv) % m;
                            int nmask = mask ^ (1 << i);
                            ans = Math.min(ans, rt + dfs(nmask, 0, nstage));
                        }
                    }
                }
                memo[mask][pos][stage] = ans;
                return ans;
            }
        }
        double res = new DfsHelper().dfs(0, 0, 0);
        return res > (INF / 2) ? -1.0 : res;
    }
}
# @lc code=end