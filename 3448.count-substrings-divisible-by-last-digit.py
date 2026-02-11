#
# @lc app=leetcode id=3448 lang=python3
#
# [3448] Count Substrings Divisible By Last Digit
#

# @lc code=start
class Solution:
    def countSubstrings(self, s: str) -> int:
        n = len(s)
        freq = [[0] * k for k in range(10)]
        ans = 0
        for i in range(n):
            dig = int(s[i])
            new_freq = [[0] * k for k in range(10)]
            for k in range(1, 10):
                for m in range(k):
                    new_mod = (m * 10 + dig) % k
                    new_freq[k][new_mod] += freq[k][m]
            for k in range(1, 10):
                new_freq[k][dig % k] += 1
            if dig > 0:
                ans += new_freq[dig][0]
            freq = new_freq
        return ans

# @lc code=end