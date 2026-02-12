#
# @lc app=leetcode id=2289 lang=java
#
# [2289] Steps to Make Array Non-decreasing
#
# @lc code=start
class Solution {
    public int totalSteps(int[] nums) {
        int n = nums.length;
        if (n == 1) return 0;
        int[] steps = new int[n];
        int maxSteps = 0;
        java.util.Stack<Integer> stack = new java.util.Stack<>();
        for (int i = n - 1; i >= 0; --i) {
            int step = 0;
            while (!stack.isEmpty() && nums[i] > nums[stack.peek()]) {
                step = Math.max(step + 1, steps[stack.pop()]);
            }
            steps[i] = step;
            maxSteps = Math.max(maxSteps, step);
            stack.push(i);
        }
        return maxSteps;
    }
}
# @lc code=end