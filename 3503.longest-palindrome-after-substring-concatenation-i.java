#
# @lc app=leetcode id=3503 lang=java
#
# [3503] Longest Palindrome After Substring Concatenation I
#

# @lc code=start
class Solution {
    public int longestPalindrome(String s, String t) {
        int maxLen = 0;
        int n = s.length(), m = t.length();
        for (int i = 0; i <= n; ++i) {
            for (int j = i; j <= n; ++j) {
                String ss = s.substring(i, j);
                for (int k = 0; k <= m; ++k) {
                    for (int l = k; l <= m; ++l) {
                        String tt = t.substring(k, l);
                        String combined = ss + tt;
                        if (combined.length() > 0 && isPalindrome(combined)) {
                            maxLen = Math.max(maxLen, combined.length());
                        }
                    }
                }
            }
        }
        return maxLen;
    }
    private boolean isPalindrome(String str) {
        int left = 0, right = str.length() - 1;
        while (left < right) {
            if (str.charAt(left) != str.charAt(right)) return false;
            left++; right--;
        }
        return true;
    }
}
# @lc code=end