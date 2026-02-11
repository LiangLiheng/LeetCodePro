#
# @lc app=leetcode id=3748 lang=java
#
# [3748] Count Stable Subarrays
#

# @lc code=start
class Solution {
    public long[] countStableSubarrays(int[] nums, int[][] queries) {
        int n = nums.length;
        int[] L = new int[n];
        L[0] = 0;
        for (int i = 1; i < n; ++i) {
            if (nums[i - 1] > nums[i]) {
                L[i] = i;
            } else {
                L[i] = L[i - 1];
            }
        }
        int[] runEnd = new int[n];
        for (int i = 0; i < n; ++i) {
            if (L[i] == i) {
                int end = i;
                while (end < n - 1 && L[end + 1] == i) {
                    ++end;
                }
                for (int k = i; k <= end; ++k) {
                    runEnd[k] = end;
                }
            }
        }
        long[] prefix = new long[n + 1];
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + (i - L[i] + 1L);
        }
        long[] ans = new long[queries.length];
        for (int qi = 0; qi < queries.length; ++qi) {
            int l = queries[qi][0];
            int r = queries[qi][1];
            long total = prefix[r + 1] - prefix[l];
            long crossing = 0;
            if (l > 0 && L[l] < l) {
                int s = L[l];
                int e = runEnd[l];
                int qend = Math.min(r, e);
                if (qend >= l) {
                    long numq = (long) qend - l + 1;
                    long nump = (long) l - s;
                    crossing = numq * nump;
                }
            }
            ans[qi] = total - crossing;
        }
        return ans;
    }
}
# @lc code=end