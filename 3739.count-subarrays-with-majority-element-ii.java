#
# @lc app=leetcode id=3739 lang=java
#
# [3739] Count Subarrays With Majority Element II
#

# @lc code=start
class Solution {
    static class FenwickTree {
        private long[] tree;
        private int n;

        public FenwickTree(int size) {
            n = size;
            tree = new long[size + 1];
        }

        public void update(int index, long value) {
            while (index <= n) {
                tree[index] += value;
                index += index & -index;
            }
        }

        public long query(int index) {
            long sum = 0;
            while (index > 0) {
                sum += tree[index];
                index -= index & -index;
            }
            return sum;
        }
    }

    public long countMajoritySubarrays(int[] nums, int target) {
        final int OFFSET = 100001;
        final int MAXV = 200010;
        FenwickTree ft = new FenwickTree(MAXV);
        ft.update(OFFSET, 1);
        int pref = 0;
        long ans = 0;
        for (int num : nums) {
            pref += (num == target ? 1 : -1);
            int idx = pref + OFFSET;
            ans += ft.query(idx - 1);
            ft.update(idx, 1);
        }
        return ans;
    }
}
# @lc code=end