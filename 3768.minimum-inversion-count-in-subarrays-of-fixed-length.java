#
# @lc app=leetcode id=3768 lang=java
#
# [3768] Minimum Inversion Count in Subarrays of Fixed Length
#

# @lc code=start
class Solution {
    private static class FenwickTree {
        private int size;
        private long[] tree;

        public FenwickTree(int n) {
            size = n;
            tree = new long[n + 2];
        }

        public void update(int idx, long val) {
            while (idx <= size) {
                tree[idx] += val;
                idx += idx & -idx;
            }
        }

        public long query(int idx) {
            long sum = 0;
            while (idx > 0) {
                sum += tree[idx];
                idx -= idx & -idx;
            }
            return sum;
        }

        public long query(int l, int r) {
            if (l > r) return 0;
            return query(r) - query(l - 1);
        }
    }

    public long minInversionCount(int[] nums, int k) {
        int n = nums.length;
        int[] vals = nums.clone();
        Arrays.sort(vals);
        int m = 0;
        int[] uniqueSorted = new int[n];
        for (int i = 0; i < n; i++) {
            if (i == 0 || vals[i] != vals[i - 1]) {
                uniqueSorted[m++] = vals[i];
            }
        }
        int[] rank = new int[n];
        for (int i = 0; i < n; i++) {
            rank[i] = Arrays.binarySearch(uniqueSorted, 0, m, nums[i]) + 1;
        }
        FenwickTree ft = new FenwickTree(m);
        long curInv = 0;
        for (int i = 0; i < k; i++) {
            int rnk = rank[i];
            curInv += ft.query(rnk + 1, m);
            ft.update(rnk, 1);
        }
        long minInv = curInv;
        int left = 0;
        for (int right = k; right < n; right++) {
            int rnkL = rank[left];
            long deltaRemove = ft.query(1, rnkL - 1);
            curInv -= deltaRemove;
            ft.update(rnkL, -1);
            int rnkR = rank[right];
            long deltaAdd = ft.query(rnkR + 1, m);
            curInv += deltaAdd;
            ft.update(rnkR, 1);
            minInv = Math.min(minInv, curInv);
            left++;
        }
        return minInv;
    }
}
# @lc code=end