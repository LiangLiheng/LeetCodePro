#
# @lc app=leetcode id=3753 lang=python3
#
# [3753] Total Waviness of Numbers in Range II
#

# @lc code=start
class Solution:
    def totalWaviness(self, num1: int, num2: int) -> int:
        def compute(num):
            if num < 1:
                return 0
            S = str(num)
            L = len(S)
            memo = {}
            def dp(pos, tight, pp, p, alen):
                if pos == L:
                    return 1, 0
                key = (pos, tight, pp, p, alen)
                if key in memo:
                    return memo[key]
                res_cnt = 0
                res_sum = 0
                up = 9 if tight == 0 else int(S[pos])
                for d in range(up + 1):
                    ntight = 1 if tight == 1 and d == up else 0
                    if alen == 0:
                        if d == 0:
                            nal = 0
                            npp = 10
                            np = 10
                            contrib = 0
                        else:
                            nal = 1
                            npp = 10
                            np = d
                            contrib = 0
                    else:
                        contrib = 0
                        if alen >= 2:
                            if p > pp and p > d:
                                contrib += 1
                            if p < pp and p < d:
                                contrib += 1
                        nal = alen + 1
                        npp = p
                        np = d
                    cnt, suma = dp(pos + 1, ntight, npp, np, nal)
                    res_cnt += cnt
                    res_sum += suma + contrib * cnt
                memo[key] = (res_cnt, res_sum)
                return memo[key]
            return dp(0, 1, 10, 10, 0)[1]
        return compute(num2) - compute(num1 - 1)
# @lc code=end