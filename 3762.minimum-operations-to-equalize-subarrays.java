#
# @lc app=leetcode id=3762 lang=java
#
# [3762] Minimum Operations to Equalize Subarrays
#

# @lc code=start
class Solution {
    public long[] minOperations(int[] nums, int k, int[][] queries) {
        int n = nums.length;
        int q = queries.length;
        long[] ans = new long[q];
        for (int idx = 0; idx < q; ++idx) {
            int l = queries[idx][0], r = queries[idx][1];
            int mod = nums[l] % k;
            boolean ok = true;
            for (int i = l + 1; i <= r; ++i) {
                if (nums[i] % k != mod) {
                    ok = false;
                    break;
                }
            }
            // Edge case: single-element subarray
            if (!ok) {
                ans[idx] = -1;
                continue;
            }
            int len = r - l + 1;
            if (len == 1) {
                ans[idx] = 0;
                continue;
            }
            int[] normalized = new int[len];
            for (int i = 0; i < len; ++i) {
                normalized[i] = (nums[l + i] - mod) / k;
            }
            java.util.Arrays.sort(normalized);
            int median = normalized[len / 2];
            long sum = 0;
            for (int v : normalized) {
                sum += Math.abs(v - median);
            }
            ans[idx] = sum;
        }
        return ans;
    }
}
# @lc code=end