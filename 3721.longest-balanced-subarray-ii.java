#
# @lc app=leetcode id=3721 lang=java
#
# [3721] Longest Balanced Subarray II
#

# @lc code=start
import java.util.*;
class Solution {
    public int longestBalanced(int[] nums) {
        int n = nums.length;
        int maxLen = 0;
        for (int left = 0; left < n; ++left) {
            Set<Integer> evenSet = new HashSet<>();
            Set<Integer> oddSet = new HashSet<>();
            for (int right = left; right < n; ++right) {
                if (nums[right] % 2 == 0) {
                    evenSet.add(nums[right]);
                } else {
                    oddSet.add(nums[right]);
                }
                if (evenSet.size() == oddSet.size()) {
                    maxLen = Math.max(maxLen, right - left + 1);
                }
            }
        }
        return maxLen;
    }
}
# @lc code=end