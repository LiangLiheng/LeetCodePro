#
# @lc app=leetcode id=3779 lang=java
#
# [3779] Minimum Number of Operations to Have Distinct Elements
#

# @lc code=start
class Solution {
    public int minOperations(int[] nums) {
        int n = nums.length;
        java.util.HashMap<Integer, Integer> lastSeen = new java.util.HashMap<>();
        int maxSecondLast = -1;
        for (int i = n - 1; i >= 0; i--) {
            int v = nums[i];
            if (lastSeen.containsKey(v)) {
                maxSecondLast = Math.max(maxSecondLast, i);
            }
            lastSeen.put(v, i);
        }
        int i0 = maxSecondLast == -1 ? 0 : maxSecondLast + 1;
        return (i0 + 2) / 3;
    }
}
# @lc code=end