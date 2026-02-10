#
# @lc app=leetcode id=3441 lang=python3
#
# [3441] Minimum Cost Good Caption
#

# @lc code=start
class Solution:
    def minCostGoodCaption(self, caption: str) -> str:
        n = len(caption)
        if n < 3:
            return ''
        INF = 10**9 + 7
        A = ord('a')
        s = [ord(c) - A for c in caption]
        dp = [[[INF] * 4 for _ in range(26)] for _ in range(n + 1)]
        for c in range(26):
            dp[1][c][1] = abs(s[0] - c)
        for i in range(1, n):
            for c in range(26):
                for r in range(1, 4):
                    if dp[i][c][r] == INF:
                        continue
                    # continue run
                    cost = abs(s[i] - c)
                    nr = min(3, r + 1)
                    dp[i + 1][c][nr] = min(dp[i + 1][c][nr], dp[i][c][r] + cost)
                    # start new run
                    if r == 3:
                        for nc in range(26):
                            if nc == c:
                                continue
                            cost = abs(s[i] - nc)
                            dp[i + 1][nc][1] = min(dp[i + 1][nc][1], dp[i][c][r] + cost)
        min_cost = INF
        for c in range(26):
            min_cost = min(min_cost, dp[n][c][3])
        if min_cost == INF:
            return ''
        # backward DP for suffix mins
        bdp = [[[INF] * 4 for _ in range(26)] for _ in range(n + 1)]
        for c in range(26):
            bdp[n][c][3] = 0
        for i in range(n - 1, -1, -1):
            for c in range(26):
                for r in range(1, 4):
                    # continue
                    cost = abs(s[i] - c)
                    nr = min(3, r + 1)
                    bdp[i][c][r] = min(bdp[i][c][r], cost + bdp[i + 1][c][nr])
                    # new run
                    if r == 3:
                        for nc in range(26):
                            if nc == c:
                                continue
                            cost = abs(s[i] - nc)
                            bdp[i][c][r] = min(bdp[i][c][r], cost + bdp[i + 1][nc][1])
        # reconstruct lex smallest
        res = [''] * n
        # pos 0
        for chosen in range(26):
            cost_add = abs(s[0] - chosen)
            new_c = chosen
            new_r = 1
            suf = bdp[1][new_c][new_r]
            if cost_add + suf == min_cost:
                res[0] = chr(A + chosen)
                prefix_cost = cost_add
                curr_c = new_c
                curr_r = new_r
                curr_i = 1
                break
        else:
            return ''  # should not happen
        # remaining
        while curr_i < n:
            pos = curr_i
            for chosen in range(26):
                if chosen == curr_c:
                    new_c = curr_c
                    new_r = min(3, curr_r + 1)
                    possible = True
                else:
                    new_c = chosen
                    new_r = 1
                    possible = (curr_r == 3)
                if not possible:
                    continue
                cost_add = abs(s[pos] - chosen)
                suf = bdp[curr_i + 1][new_c][new_r]
                if prefix_cost + cost_add + suf == min_cost:
                    res[pos] = chr(A + chosen)
                    prefix_cost += cost_add
                    curr_c = new_c
                    curr_r = new_r
                    curr_i += 1
                    break
            else:
                return ''  # error
        return ''.join(res)
# @lc code=end