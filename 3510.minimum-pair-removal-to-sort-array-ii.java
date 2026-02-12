#
# @lc app=leetcode id=3510 lang=java
#
# [3510] Minimum Pair Removal to Sort Array II
#
# @lc code=start
class Solution {
    public int minimumPairRemoval(int[] nums) {
        java.util.List<Integer> arr = new java.util.ArrayList<>();
        for (int num : nums) arr.add(num);
        int res = 0;
        while (!isNonDecreasing(arr)) {
            int minSum = Integer.MAX_VALUE;
            int minIdx = -1;
            for (int i = 0; i < arr.size() - 1; ++i) {
                int sum = arr.get(i) + arr.get(i + 1);
                if (sum < minSum) {
                    minSum = sum;
                    minIdx = i;
                }
            }
            // Merge the leftmost minimum-sum pair
            arr.set(minIdx, arr.get(minIdx) + arr.get(minIdx + 1));
            arr.remove(minIdx + 1);
            res++;
        }
        return res;
    }
    private boolean isNonDecreasing(java.util.List<Integer> arr) {
        for (int i = 1; i < arr.size(); ++i) {
            if (arr.get(i) < arr.get(i - 1)) return false;
        }
        return true;
    }
}
# @lc code=end