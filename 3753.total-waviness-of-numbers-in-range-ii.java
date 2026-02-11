#
# @lc app=leetcode id=3753 lang=java
#
# [3753] Total Waviness of Numbers in Range II
#

# @lc code=start
class Solution {
    private String s;
    private int L;
    private long[][][][] memoSum;
    private long[][][][] memoCnt;

    public long totalWaviness(long num1, long num2) {
        return calc(num2) - calc(num1 - 1);
    }

    private long calc(long n) {
        if (n < 1) return 0;
        s = String.valueOf(n);
        L = s.length();
        memoSum = new long[L + 1][2][11][11];
        memoCnt = new long[L + 1][2][11][11];
        initMemo(memoSum, -1L);
        initMemo(memoCnt, -1L);
        return dfsSum(0, 1, 10, 10);
    }

    private void initMemo(long[][][][] memo, long val) {
        for (int i = 0; i <= L; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 11; k++) {
                    for (int m = 0; m < 11; m++) {
                        memo[i][j][k][m] = val;
                    }
                }
            }
        }
    }

    private long dfsCnt(int pos, int tight, int p1, int p2) {
        if (pos == L) {
            return 1L;
        }
        if (memoCnt[pos][tight][p1][p2] != -1L) {
            return memoCnt[pos][tight][p1][p2];
        }
        long res = 0L;
        int up = tight == 1 ? s.charAt(pos) - '0' : 9;
        for (int d = 0; d <= up; d++) {
            int ntight = (tight == 1 && d == up) ? 1 : 0;
            int np1, np2;
            if (p1 == 10) {
                np1 = d == 0 ? 10 : d;
                np2 = 10;
            } else {
                np2 = p1;
                np1 = d;
            }
            res += dfsCnt(pos + 1, ntight, np1, np2);
        }
        return memoCnt[pos][tight][p1][p2] = res;
    }

    private long dfsSum(int pos, int tight, int p1, int p2) {
        if (pos == L) {
            return 0L;
        }
        if (memoSum[pos][tight][p1][p2] != -1L) {
            return memoSum[pos][tight][p1][p2];
        }
        long res = 0L;
        int up = tight == 1 ? s.charAt(pos) - '0' : 9;
        for (int d = 0; d <= up; d++) {
            int ntight = (tight == 1 && d == up) ? 1 : 0;
            int np1, np2;
            long contrib = 0L;
            if (p1 == 10) {
                // not started
                np1 = (d == 0) ? 10 : d;
                np2 = 10;
            } else {
                // started
                if (p2 != 10) {
                    int left = p2;
                    int mid = p1;
                    int right = d;
                    if ((mid > left && mid > right) || (mid < left && mid < right)) {
                        contrib = 1L;
                    }
                }
                np2 = p1;
                np1 = d;
            }
            long subcnt = dfsCnt(pos + 1, ntight, np1, np2);
            long subsum = dfsSum(pos + 1, ntight, np1, np2);
            res += contrib * subcnt + subsum;
        }
        return memoSum[pos][tight][p1][p2] = res;
    }
}
# @lc code=end