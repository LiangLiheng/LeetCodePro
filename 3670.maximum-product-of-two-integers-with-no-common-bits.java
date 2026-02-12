#
# @lc app=leetcode id=3670 lang=java
#
# [3670] Maximum Product of Two Integers With No Common Bits
#
# @lc code=start
class Solution {
    public long maxProduct(int[] nums) {
        Map<Integer, Integer> maskToMax = new HashMap<>();
        for (int x : nums) {
            int mask = x;
            maskToMax.put(mask, Math.max(maskToMax.getOrDefault(mask, 0), x));
        }
        long ans = 0;
        Integer[] masks = maskToMax.keySet().toArray(new Integer[0]);
        for (int i = 0; i < masks.length; i++) {
            for (int j = i + 1; j < masks.length; j++) {
                if ((masks[i] & masks[j]) == 0) {
                    long prod = 1L * maskToMax.get(masks[i]) * maskToMax.get(masks[j]);
                    if (prod > ans) ans = prod;
                }
            }
        }
        return ans;
    }
}
# @lc code=end