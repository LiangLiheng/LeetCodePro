#
# @lc app=leetcode id=3630 lang=java
#
# [3630] Partition Array for Maximum XOR and AND
#

# @lc code=start
class Solution {
    public long maximizeXorAndXor(int[] nums) {
        int n = nums.length;
        int half = n >> 1;
        int left_cnt = half;
        int right_cnt = n - half;
        int left_size = 1;
        for (int i = 0; i < left_cnt; i++) {
            left_size *= 3;
        }
        int right_size = 1;
        for (int i = 0; i < right_cnt; i++) {
            right_size *= 3;
        }
        long FULL_MASK = (1L << 31) - 1;
        long BIT30 = 1L << 30;
        long[] xa_left = new long[left_size];
        long[] and_left = new long[left_size];
        long[] xc_left = new long[left_size];
        for (int conf = 0; conf < left_size; conf++) {
            long xa = 0;
            long xc = 0;
            long cur_and = FULL_MASK;
            int temp = conf;
            for (int j = 0; j < left_cnt; j++) {
                int choice = temp % 3;
                temp /= 3;
                long num = nums[j];
                if (choice == 0) {
                    xa ^= num;
                } else if (choice == 1) {
                    cur_and &= num;
                } else {
                    xc ^= num;
                }
            }
            xa_left[conf] = xa;
            and_left[conf] = cur_and;
            xc_left[conf] = xc;
        }
        long[] xa_right = new long[right_size];
        long[] and_right = new long[right_size];
        long[] xc_right = new long[right_size];
        for (int conf = 0; conf < right_size; conf++) {
            long xa = 0;
            long xc = 0;
            long cur_and = FULL_MASK;
            int temp = conf;
            for (int j = 0; j < right_cnt; j++) {
                int choice = temp % 3;
                temp /= 3;
                long num = nums[half + j];
                if (choice == 0) {
                    xa ^= num;
                } else if (choice == 1) {
                    cur_and &= num;
                } else {
                    xc ^= num;
                }
            }
            xa_right[conf] = xa;
            and_right[conf] = cur_and;
            xc_right[conf] = xc;
        }
        long result = 0;
        for (int li = 0; li < left_size; li++) {
            long xa = xa_left[li];
            long xc = xc_left[li];
            long andl = and_left[li];
            for (int ri = 0; ri < right_size; ri++) {
                long total_xa = xa ^ xa_right[ri];
                long total_xc = xc ^ xc_right[ri];
                long total_and = andl & and_right[ri];
                if ((total_and & BIT30) != 0) {
                    total_and = 0;
                }
                long current = total_xa + total_xc + total_and;
                if (current > result) {
                    result = current;
                }
            }
        }
        return result;
    }
}
# @lc code=end