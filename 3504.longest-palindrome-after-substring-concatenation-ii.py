#
# @lc app=leetcode id=3504 lang=python3
#
# [3504] Longest Palindrome After Substring Concatenation II
#

# @lc code=start
class Solution:
    def longestPalindrome(self, s: str, t: str) -> int:
        n, m = len(s), len(t)
        total = s + t
        N = n + m
        ans = 1
        # Helper for center expansion
        def expand(l, r):
            res = 0
            while l >= 0 and r < N and total[l] == total[r]:
                # Ensure the palindrome spans both substrings
                if l < n <= r:
                    res = max(res, r - l + 1)
                l -= 1
                r += 1
            return res
        # Case (c): Palindromes crossing the join
        for mid in range(n - 1, n + m):
            # Odd length
            ans = max(ans, expand(mid, mid))
            # Even length
            ans = max(ans, expand(mid, mid + 1))
        # Case (a) and (b): Palindromes fully in s or t
        def max_palindrome_in_substring(s):
            L = len(s)
            res = 1
            for center in range(L):
                # Odd
                l = r = center
                while l >= 0 and r < L and s[l] == s[r]:
                    res = max(res, r - l + 1)
                    l -= 1
                    r += 1
                # Even
                l, r = center, center + 1
                while l >= 0 and r < L and s[l] == s[r]:
                    res = max(res, r - l + 1)
                    l -= 1
                    r += 1
            return res
        ans = max(ans, max_palindrome_in_substring(s))
        ans = max(ans, max_palindrome_in_substring(t))
        return ans
# @lc code=end