#
# @lc app=leetcode id=3503 lang=python3
#
# [3503] Longest Palindrome After Substring Concatenation I
#

# @lc code=start
class Solution:
    def longestPalindrome(self, s: str, t: str) -> int:
        def is_palindrome(x):
            return x == x[::-1]
        max_len = 0
        n, m = len(s), len(t)
        # Try all substrings from s
        for i in range(n + 1):
            for j in range(i, n + 1):
                sub_s = s[i:j]
                # Try all substrings from t
                for k in range(m + 1):
                    for l in range(k, m + 1):
                        sub_t = t[k:l]
                        combined = sub_s + sub_t
                        if combined and is_palindrome(combined):
                            max_len = max(max_len, len(combined))
        return max_len
# @lc code=end