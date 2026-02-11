#
# @lc app=leetcode id=3753 lang=python3
#
# [3753] Total Waviness of Numbers in Range II
#

# @lc code=start
class Solution:
    def totalWaviness(self, num1: int, num2: int) -> int:
        from functools import lru_cache
        def waviness_up_to(n: int) -> int:
            digits = list(map(int, str(n)))
            length = len(digits)
            @lru_cache(maxsize=None)
            def dp(pos, tight, window, leading_zero, sig_count):
                if pos == length:
                    return 0
                res = 0
                up = digits[pos] if tight else 9
                for d in range(0, up+1):
                    new_leading_zero = leading_zero and d == 0
                    new_sig_count = sig_count if new_leading_zero else sig_count + 1
                    new_tight = tight and (d == up)
                    # Update window with new significant digit
                    if new_leading_zero:
                        new_window = window
                    else:
                        new_window = window + (d,)
                        if len(new_window) > 3:
                            new_window = new_window[-3:]
                    # Evaluate waviness only when window has 3 digits and not at the edges
                    if not new_leading_zero and len(new_window) == 3:
                        # Only count if this digit is not the first or last significant digit
                        if new_sig_count >= 3 and pos < length-1:
                            a, b, c = new_window
                            is_peak = b > a and b > c
                            is_valley = b < a and b < c
                            waviness = 1 if (is_peak or is_valley) else 0
                        else:
                            waviness = 0
                        res += waviness + dp(pos+1, new_tight, new_window, new_leading_zero, new_sig_count)
                    else:
                        res += dp(pos+1, new_tight, new_window, new_leading_zero, new_sig_count)
                return res
            return dp(0, True, tuple(), True, 0)
        def safe_minus_one(x):
            return max(x-1, 0)
        return waviness_up_to(num2) - waviness_up_to(safe_minus_one(num1))
# @lc code=end