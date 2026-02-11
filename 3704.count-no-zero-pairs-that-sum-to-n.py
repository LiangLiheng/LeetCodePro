#
# @lc app=leetcode id=3704 lang=python3
#
# [3704] Count No-Zero Pairs That Sum to N
#

# @lc code=start
class Solution:
    def countNoZeroPairs(self, n: int) -> int:
        # Improved approach: systematically construct all no-zero pairs (a, b) such that a + b = n
        from functools import lru_cache
        digits = list(map(int, str(n)))[::-1]  # least to most significant
        L = len(digits)

        @lru_cache(None)
        def dp(pos, carry):
            if pos == L:
                # At the end, only count if carry is zero
                return 1 if carry == 0 else 0
            res = 0
            nd = digits[pos]
            # Try all possible pairs of no-zero digits (1..9)
            for a in range(1, 10):
                for b in range(1, 10):
                    s = a + b + carry
                    if s % 10 == nd:
                        res += dp(pos + 1, s // 10)
            return res
        return dp(0, 0)
# @lc code=end