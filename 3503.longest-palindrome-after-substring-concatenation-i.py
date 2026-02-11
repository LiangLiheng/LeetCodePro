#
# @lc app=leetcode id=3503 lang=python3
#
# [3503] Longest Palindrome After Substring Concatenation I
#

# @lc code=start
class Solution:
    def longestPalindrome(self, s: str, t: str) -> int:
        n = len(s)
        m = len(t)
        ans = 0
        for i in range(n + 1):
            for j in range(i, n + 1):
                ss = s[i:j]
                for k in range(m + 1):
                    for l in range(k, m + 1):
                        st = t[k:l]
                        comb = ss + st
                        if comb == comb[::-1]:
                            ans = max(ans, len(comb))
        return ans
# @lc code=end