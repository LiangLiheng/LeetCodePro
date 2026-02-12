#
# @lc app=leetcode id=3413 lang=java
#
# [3413] Maximum Coins From K Consecutive Bags
#

# @lc code=start
class Solution {
    public long maximumCoins(int[][] coins, int k) {
        Arrays.sort(coins, (a, b) -> Integer.compare(a[0], b[0]));
        int n = coins.length;
        ArrayList<long[]> intervals = new ArrayList<>();
        for (int i = 0; i < n; ++i) {
            intervals.add(new long[]{coins[i][0], coins[i][1], coins[i][2]});
        }
        ArrayList<long[]> merged = new ArrayList<>();
        for (int i = 0; i < intervals.size(); ++i) {
            long[] cur = intervals.get(i);
            if (i > 0) {
                long[] prev = intervals.get(i - 1);
                if (prev[1] + 1 < cur[0]) {
                    merged.add(new long[]{prev[1] + 1, cur[0] - 1, 0});
                }
            }
            merged.add(cur);
        }
        n = merged.size();
        long max = 0;
        int left = 0;
        for (int i = 0; i < n; ++i) {
            long windowStart = merged.get(i)[0];
            long windowEnd = windowStart + k - 1;
            long sum = 0;
            int idx = i;
            long remain = k;
            long pos = windowStart;
            while (idx < n && remain > 0) {
                long segStart = Math.max(merged.get(idx)[0], pos);
                long segEnd = Math.min(merged.get(idx)[1], windowEnd);
                if (segStart > segEnd) {
                    ++idx;
                    continue;
                }
                long len = segEnd - segStart + 1;
                sum += len * merged.get(idx)[2];
                pos = segEnd + 1;
                remain -= len;
                ++idx;
            }
            max = Math.max(max, sum);
            // Early exit if no more windows of size k can start
            if (windowStart + k - 1 > merged.get(n-1)[1]) break;
        }
        return max;
    }
}
# @lc code=end