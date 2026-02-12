#
# @lc app=leetcode id=3434 lang=java
#
# [3434] Maximum Frequency After Subarray Operation
#

# @lc code=start
class Solution {
    public int maxFrequency(int[] nums, int k) {
        int n = nums.length;
        int maxFreq = 0;
        // Count the number of k's already present
        int existingK = 0;
        for (int num : nums) {
            if (num == k) existingK++;
        }
        maxFreq = existingK;
        // Use sliding window to find the largest contiguous subarray that can be converted to all k's
        int left = 0;
        while (left < n) {
            int x = k - nums[left];
            int right = left;
            while (right < n && nums[right] + x == k) {
                right++;
            }
            // Compute frequency: length of this window + existingK outside the window
            int freq = right - left;
            if (freq > maxFreq) {
                maxFreq = freq;
            }
            left = right + 1;
        }
        return maxFreq;
    }
}
# @lc code=end