#
# @lc app=leetcode id=3630 lang=java
#
# [3630] Partition Array for Maximum XOR and AND
#

# @lc code=start
class Solution {
    public long maximizeXorAndXor(int[] nums) {
        int n = nums.length;
        return dfs(nums, 0, 0, false, 0, false, 0, false);
    }

    // Recursively assign nums[idx] to A, B, or C
    // Each group carries its current value and a flag if it's non-empty
    private long dfs(int[] nums, int idx, int xorA, boolean hasA, int andB, boolean hasB, int xorC, boolean hasC) {
        if (idx == nums.length) {
            int valA = hasA ? xorA : 0;
            int valB = hasB ? andB : 0;
            int valC = hasC ? xorC : 0;
            return (long)valA + valB + valC;
        }
        // Place nums[idx] in A
        long resA = dfs(nums, idx + 1, xorA ^ nums[idx], true, andB, hasB, xorC, hasC);
        // Place nums[idx] in B
        int newAndB = hasB ? (andB & nums[idx]) : nums[idx];
        long resB = dfs(nums, idx + 1, xorA, hasA, newAndB, true, xorC, hasC);
        // Place nums[idx] in C
        long resC = dfs(nums, idx + 1, xorA, hasA, andB, hasB, xorC ^ nums[idx], true);
        return Math.max(resA, Math.max(resB, resC));
    }
}
# @lc code=end