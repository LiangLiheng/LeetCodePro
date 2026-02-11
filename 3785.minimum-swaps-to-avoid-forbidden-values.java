#
# @lc app=leetcode id=3785 lang=java
#
# [3785] Minimum Swaps to Avoid Forbidden Values
#

# @lc code=start
class Solution {
    public int minSwaps(int[] nums, int[] forbidden) {
        int n = nums.length;
        java.util.HashMap<Integer, Integer> countNum = new java.util.HashMap<>();
        java.util.HashMap<Integer, Integer> countForb = new java.util.HashMap<>();
        java.util.HashMap<Integer, Integer> countBad = new java.util.HashMap<>();
        int bad = 0;
        int maxBad = 0;
        for (int i = 0; i < n; i++) {
            countNum.put(nums[i], countNum.getOrDefault(nums[i], 0) + 1);
            countForb.put(forbidden[i], countForb.getOrDefault(forbidden[i], 0) + 1);
            if (nums[i] == forbidden[i]) {
                int v = nums[i];
                int curBad = countBad.getOrDefault(v, 0) + 1;
                countBad.put(v, curBad);
                maxBad = Math.max(maxBad, curBad);
                bad++;
            }
        }
        for (int v : countNum.keySet()) {
            int tot = countNum.get(v);
            int fb = countForb.getOrDefault(v, 0);
            if (tot > n - fb) {
                return -1;
            }
        }
        if (bad == 0) return 0;
        int match = Math.min(bad / 2, bad - maxBad);
        return bad - match;
    }
}
# @lc code=end