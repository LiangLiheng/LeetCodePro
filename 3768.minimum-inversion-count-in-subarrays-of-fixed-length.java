#
# @lc app=leetcode id=3768 lang=java
#
# [3768] Minimum Inversion Count in Subarrays of Fixed Length
#
# @lc code=start
class Solution {
    // Fenwick Tree implementation
    class Fenwick {
        int[] tree;
        int n;
        Fenwick(int n) {
            this.n = n + 2;
            tree = new int[this.n];
        }
        void update(int i, int delta) {
            i++;
            while (i < n) {
                tree[i] += delta;
                i += i & -i;
            }
        }
        int query(int i) { // sum[0..i]
            i++;
            int res = 0;
            while (i > 0) {
                res += tree[i];
                i -= i & -i;
            }
            return res;
        }
        int range(int l, int r) {
            return query(r) - query(l - 1);
        }
    }
    public long minInversionCount(int[] nums, int k) {
        int n = nums.length;
        int[] sorted = nums.clone();
        java.util.Arrays.sort(sorted);
        java.util.Map<Integer, Integer> compress = new java.util.HashMap<>();
        int idx = 0;
        for (int val : sorted) {
            if (!compress.containsKey(val)) compress.put(val, idx++);
        }
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) arr[i] = compress.get(nums[i]);
        Fenwick bit = new Fenwick(idx);
        long inv = 0;
        // Compute initial window inversions
        for (int i = 0; i < k; i++) {
            inv += i - bit.query(arr[i]);
            bit.update(arr[i], 1);
        }
        long minInv = inv;
        for (int i = k; i < n; i++) {
            // Remove arr[i-k]
            bit.update(arr[i - k], -1);
            inv -= bit.query(arr[i - k] - 1);
            // Add arr[i]
            inv += bit.range(arr[i] + 1, idx - 1);
            bit.update(arr[i], 1);
            // Sanity check: inversion count should not be negative
            assert inv >= 0 : "Inversion count became negative, check window updates and indices.";
            minInv = Math.min(minInv, inv);
        }
        // Final verification for simple edge cases
        if (k == 1 || java.util.Arrays.stream(nums).distinct().count() == 1) {
            assert minInv == 0 : "Edge case failed: expected zero inversions.";
        }
        return minInv;
    }
}
# @lc code=end