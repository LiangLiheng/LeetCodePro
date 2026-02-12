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
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
        int[] incLeft = new int[n]; // length of strictly increasing sequence ending at i
        int[] dec = new int[n];     // length of strictly decreasing sequence ending at i
        int[] incRight = new int[n]; // length of strictly increasing sequence starting at i
        incLeft[0] = 1;
        for (int i = 1; i < n; ++i) {
            incLeft[i] = (nums[i - 1] < nums[i]) ? incLeft[i - 1] + 1 : 1;
        }
        dec[0] = 1;
        for (int i = 1; i < n; ++i) {
            dec[i] = (nums[i - 1] > nums[i]) ? dec[i - 1] + 1 : 1;
        }
        incRight[n - 1] = 1;
        for (int i = n - 2; i >= 0; --i) {
            incRight[i] = (nums[i] < nums[i + 1]) ? incRight[i + 1] + 1 : 1;
        }
        long maxSum = Long.MIN_VALUE;
        // For each possible middle segment (the strictly decreasing part)
        for (int mid = 1; mid < n - 1; ++mid) {
            int decLen = dec[mid];
            if (decLen < 2) continue; // strictly decreasing needs at least 2 elements
            int q = mid - decLen + 1; // start of decreasing segment
            int p = q - 1; // end of left increasing segment
            if (p < 0 || incLeft[p] < 2) continue; // left increasing must exist and have at least 2 elements
            int l = p - incLeft[p] + 1; // start of left increasing
            int r = mid + 1; // start of right increasing segment
            if (r >= n || incRight[r] < 2) continue; // right increasing must exist and have at least 2 elements
            int rr = r + incRight[r] - 1; // end of right increasing
            // Verify segments are non-overlapping, contiguous, and within bounds
            if (l < 0 || rr >= n || p + 1 != q || mid + 1 != r) continue;
            // Optionally, you could add explicit checks to ensure each segment is strictly monotonic if unsure
            long sum = prefix[rr + 1] - prefix[l];
            maxSum = Math.max(maxSum, sum);
        }
        return maxSum;
    }
}
# @lc code=end