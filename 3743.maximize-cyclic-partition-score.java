#
# @lc app=leetcode id=3743 lang=java
#
# [3743] Maximize Cyclic Partition Score
#

# @lc code=start
class Solution {
    public long maximumScore(int[] nums, int k) {
        int n = nums.length;
        int[] sorted = nums.clone();
        java.util.Arrays.sort(sorted);
        long[] prefix = new long[n + 1];
        for (int i = 1; i <= n; ++i) {
            prefix[i] = prefix[i - 1] + sorted[i - 1];
        }
        long ans = 0;
        int maxM = Math.min(k, n);
        for (int m = 1; m <= maxM; ++m) {
            long sumSmall = prefix[m];
            long sumLarge = prefix[n] - prefix[n - m];
            ans = Math.max(ans, sumLarge - sumSmall);
        }
        return ans;
    }
}
# @lc code=end