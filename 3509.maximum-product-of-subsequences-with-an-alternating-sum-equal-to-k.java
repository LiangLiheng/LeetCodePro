#
# @lc app=leetcode id=3509 lang=java
#
# [3509] Maximum Product of Subsequences With an Alternating Sum Equal to K
#
# @lc code=start
class Solution {
    public int maxProduct(int[] nums, int k, int limit) {
        final int SHIFT = 1800;
        final int MAX_S = 3601;
        final int MAX_V = 12;
        int n = nums.length;
        int[][][][] curr = new int[2][2][MAX_S][MAX_V + 1];
        // Initialize curr to -1
        for (int u = 0; u < 2; ++u) {
            for (int p = 0; p < 2; ++p) {
                for (int s = 0; s < MAX_S; ++s) {
                    for (int b = 0; b <= MAX_V; ++b) {
                        curr[u][p][s][b] = -1;
                    }
                }
            }
        }
        // Initial empty: used=0, par=0, ss=SHIFT, prod=1
        for (int d = 1; d <= MAX_V; ++d) {
            int thresh = limit / d;
            if (1 <= thresh) {
                curr[0][0][SHIFT][d] = 1;
            }
        }
        for (int i = 0; i < n; ++i) {
            int[][][][] nextDp = new int[2][2][MAX_S][MAX_V + 1];
            // Initialize nextDp to -1
            for (int u = 0; u < 2; ++u) {
                for (int p = 0; p < 2; ++p) {
                    for (int s = 0; s < MAX_S; ++s) {
                        for (int b = 0; b <= MAX_V; ++b) {
                            nextDp[u][p][s][b] = -1;
                        }
                    }
                }
            }
            int val = nums[i];
            for (int used = 0; used < 2; ++used) {
                for (int par = 0; par < 2; ++par) {
                    for (int ss = 0; ss < MAX_S; ++ss) {
                        if (curr[used][par][ss][1] == -1) continue;
                        // skip: copy buckets
                        for (int d = 1; d <= MAX_V; ++d) {
                            nextDp[used][par][ss][d] = Math.max(nextDp[used][par][ss][d], curr[used][par][ss][d]);
                        }
                        // take
                        int signn = (par == 0 ? 1 : -1);
                        int delta = signn * val;
                        int nss = ss + delta;
                        if (nss < 0 || nss >= MAX_S) continue;
                        int npar = 1 - par;
                        int nused = 1;
                        int nprod = -1;
                        if (val == 0) {
                            nprod = 0;
                        } else {
                            int buck = val;
                            int mold = curr[used][par][ss][buck];
                            if (mold == -1) continue;
                            long nlprod = (long) mold * val;
                            if (nlprod > limit) continue;
                            nprod = (int) nlprod;
                        }
                        // update new state's buckets
                        for (int e = 1; e <= MAX_V; ++e) {
                            int thresh = limit / e;
                            if (nprod <= thresh) {
                                nextDp[nused][npar][nss][e] = Math.max(nextDp[nused][npar][nss][e], nprod);
                            }
                        }
                    }
                }
            }
            curr = nextDp;
        }
        int ts = SHIFT + k;
        int answer = -1;
        if (ts >= 0 && ts < MAX_S) {
            for (int par = 0; par < 2; ++par) {
                int mp = curr[1][par][ts][1];
                if (mp != -1) {
                    answer = Math.max(answer, mp);
                }
            }
        }
        return answer;
    }
}
# @lc code=end