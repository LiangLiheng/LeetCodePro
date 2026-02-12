#
# @lc app=leetcode id=3525 lang=java
#
# [3525] Find X Value of Array II
#
# @lc code=start
class Solution {
    public int[] resultArray(int[] nums, int k, int[][] queries) {
        int n = nums.length;
        int q = queries.length;
        int[] res = new int[q];
        for (int queryIdx = 0; queryIdx < q; ++queryIdx) {
            int index = queries[queryIdx][0];
            int value = queries[queryIdx][1];
            int start = queries[queryIdx][2];
            int xi = queries[queryIdx][3];
            // Verify valid index and update
            if (index >= 0 && index < n) {
                nums[index] = value;
            }
            // Remove prefix
            int m = n - start;
            if (m <= 0) {
                res[queryIdx] = 0;
                continue;
            }
            int[] arr = new int[m];
            for (int i = 0; i < m; ++i) arr[i] = nums[start + i];
            int[] dp = new int[k];
            for (int i = m - 1; i >= 0; --i) {
                int[] ndp = new int[k];
                int mod = arr[i] % k;
                ndp[mod] += 1; // Single element suffix
                for (int r = 0; r < k; ++r) {
                    int newR = (r * mod) % k;
                    ndp[newR] += dp[r];
                }
                dp = ndp;
            }
            // Double-check: dp[xi] should count all non-empty suffixes with product mod k == xi
            res[queryIdx] = dp[xi];
        }
        return res;
    }
}
# @lc code=end