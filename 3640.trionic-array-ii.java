#
# @lc app=leetcode id=3640 lang=java
#
# [3640] Trionic Array II
#

# @lc code=start
class Solution {
    public long maxSumTrionic(int[] nums) {
        int n = nums.length;
        long[] prefix = new long[n + 1];
        for (int i = 1; i <= n; ++i) {
            prefix[i] = prefix[i - 1] + nums[i - 1];
        }
        int[] left_inc = new int[n];
        long[] left_min_pref = new long[n];
        left_inc[0] = 0;
        left_min_pref[0] = Long.MAX_VALUE / 2;
        for (int i = 1; i < n; ++i) {
            if (nums[i - 1] < nums[i]) {
                left_inc[i] = left_inc[i - 1];
                left_min_pref[i] = Math.min(left_min_pref[i - 1], prefix[i - 1]);
            } else {
                left_inc[i] = i;
                left_min_pref[i] = Long.MAX_VALUE / 2;
            }
        }
        int[] right_inc = new int[n];
        long[] right_max_pref = new long[n];
        right_inc[n - 1] = n - 1;
        right_max_pref[n - 1] = Long.MIN_VALUE / 2;
        for (int i = n - 2; i >= 0; --i) {
            if (nums[i] < nums[i + 1]) {
                right_inc[i] = right_inc[i + 1];
                right_max_pref[i] = Math.max(prefix[i + 2], right_max_pref[i + 1]);
            } else {
                right_inc[i] = i;
                right_max_pref[i] = Long.MIN_VALUE / 2;
            }
        }
        int[] right_dec = new int[n];
        right_dec[n - 1] = n - 1;
        for (int i = n - 2; i >= 0; --i) {
            if (nums[i] > nums[i + 1]) {
                right_dec[i] = right_dec[i + 1];
            } else {
                right_dec[i] = i;
            }
        }
        long ans = Long.MIN_VALUE;
        for (int p = 1; p < n - 1; ++p) {
            if (nums[p - 1] < nums[p] && nums[p] > nums[p + 1]) {
                int q = right_dec[p];
                if (q < n - 1 && nums[q] < nums[q + 1]) {
                    long cur = right_max_pref[q] - left_min_pref[p];
                    if (cur > ans) {
                        ans = cur;
                    }
                }
            }
        }
        return ans;
    }
}
# @lc code=end