/*
 * @lc app=leetcode id=3677 lang=java
 *
 * [3677] Count Binary Palindromic Numbers
 */
// @lc code=start
class Solution {
    public int countBinaryPalindromes(long n) {
        int count = (n >= 0) ? 1 : 0; // count 0 if in range
        int maxBits = Long.toBinaryString(n).length();
        for (int len = 1; len <= maxBits; len++) {
            int half = (len + 1) / 2;
            long start = 1L << (half - 1);
            long end = 1L << half;
            for (long i = start; i < end; i++) {
                long pal = createPalindrome(i, len % 2 == 1);
                if (pal > n) break;
                if (pal != 0) count++;
            }
        }
        return count;
    }
    private long createPalindrome(long x, boolean odd) {
        long res = x;
        if (odd) x >>= 1;
        while (x > 0) {
            res = (res << 1) | (x & 1);
            x >>= 1;
        }
        return res;
    }
}
// @lc code=end