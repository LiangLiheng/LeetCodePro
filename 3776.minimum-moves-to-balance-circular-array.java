#
# @lc app=leetcode id=3776 lang=java
#
# [3776] Minimum Moves to Balance Circular Array
#

# @lc code=start
class Solution {
    public long minMoves(int[] balance) {
        int n = balance.length;
        long total = 0;
        int negIdx = -1;
        long deficit = 0;
        for (int i = 0; i < n; i++) {
            total += (long) balance[i];
            if (balance[i] < 0) {
                negIdx = i;
                deficit = - (long) balance[i];
            }
        }
        if (total < 0) {
            return -1;
        }
        if (deficit == 0) {
            return 0;
        }
        int maxCost = n / 2;
        long[] capPerCost = new long[maxCost + 1];
        for (int i = 0; i < n; i++) {
            if (i == negIdx) continue;
            int diff = Math.abs(i - negIdx);
            int cost = Math.min(diff, n - diff);
            capPerCost[cost] += (long) balance[i];
        }
        long moves = 0;
        long remain = deficit;
        for (int c = 1; c <= maxCost; c++) {
            long take = Math.min(remain, capPerCost[c]);
            moves += take * (long) c;
            remain -= take;
            if (remain <= 0) break;
        }
        return moves;
    }
}
# @lc code=end