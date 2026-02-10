#
# @lc app=leetcode id=3413 lang=python3
#
# [3413] Maximum Coins From K Consecutive Bags
#

# @lc code=start
from typing import List
import bisect

class Solution:
    def maximumCoins(self, coins: List[List[int]], k: int) -> int:
        if not coins:
            return 0
        coins.sort(key=lambda x: x[0])
        m = len(coins)
        L = [c[0] for c in coins]
        R = [c[1] for c in coins]
        C = [c[2] for c in coins]
        LEN = [R[i] - L[i] + 1 for i in range(m)]
        prefix_coin = [0] * (m + 1)
        for i in range(m):
            prefix_coin[i + 1] = prefix_coin[i] + C[i] * LEN[i]
        def get_coin(p: int) -> int:
            j = bisect.bisect_left(L, p + 1)
            if j > 0 and L[j - 1] <= p <= R[j - 1]:
                return C[j - 1]
            return 0
        def get_prefix(x: int) -> int:
            if x < 1:
                return 0
            j = bisect.bisect_left(L, x + 1)
            if j == 0:
                return 0
            if L[j - 1] <= x <= R[j - 1]:
                return prefix_coin[j - 1] + C[j - 1] * (x - L[j - 1] + 1)
            return prefix_coin[j]
        changes = set()
        for i in range(m):
            changes.add(L[i])
            changes.add(R[i] + 1)
        crit_s = set(changes)
        for e in list(changes):
            crit_s.add(e - k)
        crit_list = sorted(crit_s)
        ans = 0
        for i in range(m):
            ans = max(ans, C[i] * min(k, LEN[i]))
        n_crit = len(crit_list)
        for t in range(n_crit - 1):
            left_s = crit_list[t]
            right_s = crit_list[t + 1] - 1
            if left_s > right_s:
                continue
            s0 = left_s
            delta = get_coin(s0 + k) - get_coin(s0)
            if delta > 0:
                s_eval = right_s
            elif delta < 0:
                s_eval = left_s
            else:
                s_eval = left_s
            curr = get_prefix(s_eval + k - 1) - get_prefix(s_eval - 1)
            ans = max(ans, curr)
        return ans

# @lc code=end