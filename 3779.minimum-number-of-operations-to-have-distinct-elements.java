#
# @lc app=leetcode id=3779 lang=java
#
# [3779] Minimum Number of Operations to Have Distinct Elements
#
# @lc code=start
class Solution {
    public int minOperations(int[] nums) {
        int n = nums.length;
        int ops = 0;
        int start = 0;
        while (start < n) {
            // Check if the current subarray is all distinct
            java.util.Set<Integer> set = new java.util.HashSet<>();
            for (int i = start; i < n; i++) set.add(nums[i]);
            if (set.size() == n - start) break;
            // Remove up to first three elements
            start = Math.min(n, start + 3);
            ops++;
        }
        return ops;
    }
}
# @lc code=end