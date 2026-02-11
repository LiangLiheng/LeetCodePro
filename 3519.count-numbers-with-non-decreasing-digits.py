#
# @lc app=leetcode id=3519 lang=python3
#
# [3519] Count Numbers with Non-Decreasing Digits
#

# @lc code=start
from functools import lru_cache

class Solution:
    def countNumbers(self, l: str, r: str, b: int) -> int:
        MOD = 10**9 + 7

        def get_digits(n: int, base: int) -> list[int]:
            if n == 0:
                return []
            digits = []
            while n > 0:
                digits.append(n % base)
                n //= base
            digits.reverse()
            return digits

        def count_up_to(s: str, base: int) -> int:
            n = int(s)
            D = get_digits(n, base)
            if not D:
                return 0
            L = len(D)
            @lru_cache(maxsize=None)
            def dp(pos: int, prev: int, tight: int, started: int) -> int:
                if pos == L:
                    return 1 if started == 1 else 0
                ans = 0
                upper = D[pos] if tight == 1 else base - 1
                for d in range(upper + 1):
                    ntight = 1 if tight == 1 and d == D[pos] else 0
                    nstarted = 1 if started == 1 or d > 0 else 0
                    if nstarted == 0:
                        ans = (ans + dp(pos + 1, -1, ntight, 0)) % MOD
                    else:
                        if prev != -1 and d < prev:
                            continue
                        nprev = d
                        ans = (ans + dp(pos + 1, nprev, ntight, 1)) % MOD
                return ans
            return dp(0, -1, 1, 0)

        res_r = count_up_to(r, b)
        l_num = int(l)
        if l_num == 0:
            res_l = 0
        else:
            res_l = count_up_to(str(l_num - 1), b)
        return (res_r - res_l + MOD) % MOD

# @lc code=end