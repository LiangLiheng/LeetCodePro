#
# @lc app=leetcode id=3445 lang=java
#
# [3445] Maximum Difference Between Even and Odd Frequency II
#

# @lc code=start
class Solution {
    public int maxDifference(String s, int k) {
        int n = s.length();
        int maxDiff = Integer.MIN_VALUE;
        // Only 5 digits: '0'-'4'
        for (int left = 0; left <= n-k; ++left) {
            int[] freq = new int[5];
            for (int right = left; right < n; ++right) {
                freq[s.charAt(right)-'0']++;
                if (right-left+1 >= k) {
                    // For every (a, b)
                    for (int a = 0; a < 5; ++a) {
                        if (freq[a]%2 == 1) { // odd freq
                            for (int b = 0; b < 5; ++b) {
                                if (a != b && freq[b] > 0 && freq[b]%2 == 0) { // even, nonzero
                                    maxDiff = Math.max(maxDiff, freq[a] - freq[b]);
                                }
                            }
                        }
                    }
                }
            }
        }
        return maxDiff == Integer.MIN_VALUE ? -1 : maxDiff;
    }
}
# @lc code=end