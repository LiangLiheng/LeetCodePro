#
# @lc app=leetcode id=3470 lang=python3
#
# [3470] Permutations IV
#

# @lc code=start
class Solution:
    def permute(self, n: int, k: int) -> List[int]:
        dp = [[[0] * 2 for _ in range(51)] for _ in range(51)]
        dp[0][0][0] = 1
        dp[0][0][1] = 1
        for o in range(51):
            for e in range(51):
                if o == 0 and e == 0:
                    continue
                if o > 0:
                    dp[o][e][1] = o * dp[o - 1][e][0]
                if e > 0:
                    dp[o][e][0] = e * dp[o][e - 1][1]
        num_o = (n + 1) // 2
        num_e = n // 2
        total = dp[num_o][num_e][0] + dp[num_o][num_e][1]
        if k > total:
            return []
        used = set()
        res = []
        remain_o = num_o
        remain_e = num_e
        prev_par = -1
        curr_k = k
        for i in range(n):
            for c in range(1, n + 1):
                if c in used:
                    continue
                par = c % 2
                if i > 0 and par == prev_par:
                    continue
                o_after = remain_o - (1 if par == 1 else 0)
                e_after = remain_e - (1 if par == 0 else 0)
                next_p = 1 - par
                ways = dp[o_after][e_after][next_p]
                if curr_k <= ways:
                    res.append(c)
                    used.add(c)
                    remain_o = o_after
                    remain_e = e_after
                    prev_par = par
                    break
                else:
                    curr_k -= ways
            else:
                return []
        return res

# @lc code=end