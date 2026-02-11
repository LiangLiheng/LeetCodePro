#
# @lc app=leetcode id=3519 lang=python3
#
# [3519] Count Numbers with Non-Decreasing Digits
#

# @lc code=start
class Solution:
    def countNumbers(self, l: str, r: str, b: int) -> int:
        MOD = 10 ** 9 + 7
        from functools import lru_cache

        # Convert integer n (in decimal) to base-b as list of ints
        def to_base(n: int, base: int) -> list:
            if n == 0: return [0]
            res = []
            while n > 0:
                res.append(n % base)
                n //= base
            return res[::-1]

        # Decrement a decimal string by 1
        def str_dec_base10(s: str) -> str:
            n = list(map(int, s))
            i = len(n) - 1
            while i >= 0:
                if n[i] > 0:
                    n[i] -= 1
                    break
                else:
                    n[i] = 9
                    i -= 1
            # Remove leading zeros
            res = ''.join(map(str, n)).lstrip('0')
            return res if res else '0'

        # Count numbers <= n_str (decimal string) whose base-b digits are non-decreasing
        def count(n_str: str) -> int:
            n = int(n_str)
            digits = to_base(n, b)
            sz = len(digits)

            @lru_cache(maxsize=None)
            def dp(pos, prev_digit, tight, leading_zero):
                if pos == sz:
                    # Valid if number is not only leading zeros (except for number zero itself)
                    return 0 if leading_zero else 1
                ans = 0
                max_digit = digits[pos] if tight else b - 1
                for d in range(0, max_digit + 1):
                    next_leading_zero = leading_zero and d == 0
                    # If still leading zeros, prev_digit stays as -1 (no digit chosen yet), and allow any digit
                    if next_leading_zero:
                        # Only allow number zero itself to be counted (when all digits are zero)
                        ans += dp(pos + 1, -1, tight and d == max_digit, True)
                    else:
                        # If not in leading zeros, enforce non-decreasing constraint
                        if prev_digit == -1 or d >= prev_digit:
                            ans += dp(pos + 1, d, tight and d == max_digit, False)
                return ans % MOD

            return dp(0, -1, True, True)

        l_minus_1 = str_dec_base10(l)
        res = (count(r) - count(l_minus_1)) % MOD
        return res
# @lc code=end