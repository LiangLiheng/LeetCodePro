#
# @lc app=leetcode id=3748 lang=java
#
# [3748] Count Stable Subarrays
#
# @lc code=start
class Solution {
    public long[] countStableSubarrays(int[] nums, int[][] queries) {
        int n = nums.length;
        int[] len = new int[n];
        len[0] = 1;
        for (int i = 1; i < n; ++i) {
            if (nums[i] >= nums[i-1]) {
                len[i] = len[i-1] + 1;
            } else {
                len[i] = 1;
            }
        }
        int q = queries.length;
        long[] ans = new long[q];
        for (int qi = 0; qi < q; ++qi) {
            int l = queries[qi][0];
            int r = queries[qi][1];
            long count = 0;
            for (int i = l; i <= r; ++i) {
                int segLen = Math.min(len[i], i-l+1);
                count += segLen;
            }
            ans[qi] = count;
        }
        return ans;
    }
}
# @lc code=end