#
# @lc app=leetcode id=3704 lang=python3
#
# [3704] Count No-Zero Pairs That Sum to N
#

# @lc code=start
class Solution:
    def countNoZeroPairs(self, n: int) -> int:
        s = str(n)
        L = len(s)
        digits = [int(c) for c in s[::-1]]
        total = 0
        for la in range(1, L + 1):
            allowed_a = [[] for _ in range(L)]
            msb_a = la - 1
            for p in range(L):
                if p > msb_a:
                    allowed_a[p] = [0]
                elif p == msb_a:
                    allowed_a[p] = list(range(1, 10))
                else:
                    allowed_a[p] = list(range(1, 10))
            for lb in range(1, L + 1):
                allowed_b = [[] for _ in range(L)]
                msb_b = lb - 1
                for p in range(L):
                    if p > msb_b:
                        allowed_b[p] = [0]
                    elif p == msb_b:
                        allowed_b[p] = list(range(1, 10))
                    else:
                        allowed_b[p] = list(range(1, 10))
                memo = [[-1] * 3 for _ in range(L + 1)]
                def rec(pos: int, carry: int) -> int:
                    if pos == L:
                        return 1 if carry == 0 else 0
                    if memo[pos][carry] != -1:
                        return memo[pos][carry]
                    res = 0
                    for da in allowed_a[pos]:
                        for db in allowed_b[pos]:
                            tot = da + db + carry
                            if tot % 10 == digits[pos]:
                                ncarry = tot // 10
                                res += rec(pos + 1, ncarry)
                    memo[pos][carry] = res
                    return res
                total += rec(0, 0)
        return total
# @lc code=end