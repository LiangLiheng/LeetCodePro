#
# @lc app=leetcode id=3503 lang=java
#
# [3503] Longest Palindrome After Substring Concatenation I
#
# @lc code=start
class Solution {
    private boolean isPalindrome(String str) {
        int left = 0;
        int right = str.length() - 1;
        while (left < right) {
            if (str.charAt(left++) != str.charAt(right--)) {
                return false;
            }
        }
        return true;
    }

    public int longestPalindrome(String s, String t) {
        int n = s.length();
        int m = t.length();
        int ans = 0;
        // s only palindromes (empty t)
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (isPalindrome(s.substring(i, j))) {
                    ans = Math.max(ans, j - i);
                }
            }
        }
        // t only palindromes (empty s)
        for (int i = 0; i < m; ++i) {
            for (int j = i + 1; j <= m; ++j) {
                if (isPalindrome(t.substring(i, j))) {
                    ans = Math.max(ans, j - i);
                }
            }
        }
        // both non-empty
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                String leftPart = s.substring(i, j);
                for (int p = 0; p < m; ++p) {
                    for (int q = p + 1; q <= m; ++q) {
                        String rightPart = t.substring(p, q);
                        String combined = leftPart + rightPart;
                        if (isPalindrome(combined)) {
                            ans = Math.max(ans, combined.length());
                        }
                    }
                }
            }
        }
        return ans;
    }
}
# @lc code=end