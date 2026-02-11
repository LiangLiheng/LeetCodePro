#
# @lc app=leetcode id=3448 lang=python3
#
# [3448] Count Substrings Divisible By Last Digit
#

# @lc code=start
class Solution:
    def countSubstrings(self, s: str) -> int:
        n = len(s)
        res = 0
        # For each end position
        for i in range(n):
            last_digit = int(s[i])
            if last_digit == 0:
                continue  # cannot divide by zero
            val = 0
            power = 1
            # For each substring ending at i, go backwards (up to 10 digits for efficiency)
            for j in range(i, max(-1, i-10), -1):
                val = int(s[j]) * power + val
                if val % last_digit == 0:
                    res += 1
                power *= 10
        return res
# @lc code=end