#
# @lc app=leetcode id=3441 lang=python3
#
# [3441] Minimum Cost Good Caption
#

# @lc code=start
class Solution:
    def minCostGoodCaption(self, caption: str) -> str:
        n = len(caption)
        if n == 0:
            return ''
        s = [ord(ch) - ord('a') for ch in caption]
        C = 26
        RL = 3
        INF = 10**9 + 7
        back = [[[INF] * RL for _ in range(C)] for _ in range(n + 1)]
        best = [[[26] * RL for _ in range(C)] for _ in range(n)]
        for c in range(C):
            back[n][c][2] = 0
        for i in range(n - 1, -1, -1):
            for prev in range(C):
                for prl in range(RL):
                    minv = INF
                    bnew = 26
                    for newc in range(C):
                        add_cost = abs(newc - s[i])
                        if newc == prev:
                            nrl = min(2, prl + 1)
                        else:
                            if prl != 2:
                                continue
                            nrl = 0
                        temp = add_cost + back[i + 1][newc][nrl]
                        if temp < minv:
                            minv = temp
                            bnew = newc
                    back[i][prev][prl] = minv
                    best[i][prev][prl] = bnew
        global_min = INF
        for cand in range(C):
            addc = abs(cand - s[0])
            tot = addc + back[1][cand][0]
            if tot < global_min:
                global_min = tot
        if global_min == INF:
            return ''
        # reconstruct lex smallest
        res = []
        # first char
        first_cand = 26
        for cand in range(C):
            addc = abs(cand - s[0])
            tot = addc + back[1][cand][0]
            if tot == global_min:
                first_cand = cand
                break
        res.append(chr(ord('a') + first_cand))
        prev_c = first_cand
        rl = 0
        i_now = 1
        while i_now < n:
            cand = best[i_now][prev_c][rl]
            res.append(chr(ord('a') + cand))
            if cand == prev_c:
                rl = min(2, rl + 1)
            else:
                rl = 0
            prev_c = cand
            i_now += 1
        return ''.join(res)
# @lc code=end