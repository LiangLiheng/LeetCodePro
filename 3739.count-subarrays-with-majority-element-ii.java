//
// @lc app=leetcode id=3739 lang=java
//
// [3739] Count Subarrays With Majority Element II
//

// @lc code=start
class Solution {
    public long countMajoritySubarrays(int[] nums, int target) {
        int n = nums.length;
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = nums[i] == target ? 1 : -1;
        }
        // To avoid negative prefix sums, use coordinate compression
        int[] prefixSums = new int[n + 1];
        prefixSums[0] = 0;
        for (int i = 0; i < n; i++) {
            prefixSums[i + 1] = prefixSums[i] + arr[i];
        }
        java.util.Set<Integer> set = new java.util.HashSet<>();
        for (int ps : prefixSums) set.add(ps);
        java.util.List<Integer> sorted = new java.util.ArrayList<>(set);
        java.util.Collections.sort(sorted);
        java.util.Map<Integer, Integer> index = new java.util.HashMap<>();
        for (int i = 0; i < sorted.size(); i++) index.put(sorted.get(i), i + 1); // 1-indexed for BIT

        // Fenwick Tree for prefix sum counts
        class BIT {
            long[] bit;
            int size;
            BIT(int n) { bit = new long[n + 2]; size = n + 2; }
            void add(int i, long v) { while (i < size) { bit[i] += v; i += i & -i; } }
            long sum(int i) { long res = 0; while (i > 0) { res += bit[i]; i -= i & -i; } return res; }
        }
        BIT bit = new BIT(sorted.size() + 2);
        long ans = 0;
        for (int i = 0; i <= n; i++) {
            int idx = index.get(prefixSums[i]);
            // For current prefix sum, count number of prefix sums strictly less than current
            ans += bit.sum(idx - 1);
            bit.add(idx, 1);
        }
        return ans;
    }
}
// @lc code=end