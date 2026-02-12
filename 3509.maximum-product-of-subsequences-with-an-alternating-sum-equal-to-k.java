#
# @lc app=leetcode id=3509 lang=java
#
# [3509] Maximum Product of Subsequences With an Alternating Sum Equal to K
#
# @lc code=start
import java.util.HashMap;
import java.util.Map;

class Solution {
    public int maxProduct(int[] nums, int k, int limit) {
        int n = nums.length;
        // Use a HashMap for memoization to avoid out-of-bounds with alternating sum
        Map<String, Integer> memo = new HashMap<>();
        int[] res = new int[]{-1};
        dfs(nums, k, limit, 0, 0, 0, 1, false, memo, res);
        return res[0];
    }

    void dfs(int[] nums, int k, int limit, int i, int sum, int parity, int prod, boolean taken, Map<String, Integer> memo, int[] res) {
        if (prod > limit) return;
        if (i == nums.length) {
            if (taken && sum == k) {
                if (prod > res[0]) res[0] = prod;
            }
            return;
        }
        // Key as string to handle all possible sum values
        String key = i + "," + sum + "," + parity;
        if (memo.containsKey(key) && memo.get(key) >= prod) return;
        memo.put(key, prod);
        // Skip current element
        dfs(nums, k, limit, i+1, sum, parity, prod, taken, memo, res);
        // Include current element
        int newSum = parity == 0 ? sum + nums[i] : sum - nums[i];
        dfs(nums, k, limit, i+1, newSum, 1-parity, prod * nums[i], true, memo, res);
    }
}
# @lc code=end