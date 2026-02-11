#
# @lc app=leetcode id=3562 lang=python3
#
# [3562] Maximum Profit from Trading Stocks with Discounts
#

# @lc code=start
from typing import List

class Solution:
    def maxProfit(self, n: int, present: List[int], future: List[int], hierarchy: List[List[int]], budget: int) -> int:
        present = [0] + present
        future = [0] + future
        adj = [[] for _ in range(n + 1)]
        for a, b in hierarchy:
            adj[a].append(b)
        INF = 10**9 + 7
        memo = {}

        def dfs(u: int, disc: int):
            key = (u, disc)
            if key in memo:
                return memo[key]
            cost = present[u] // 2 if disc else present[u]
            prof = future[u] - cost
            children = adj[u]
            comb0 = combine(children, 0)
            comb1 = combine(children, 1)
            dp_no = comb0[:]
            dp_yes = [-INF] * (budget + 1)
            for k in range(budget + 1):
                if k >= cost:
                    dp_yes[k] = prof + comb1[k - cost]
            memo[key] = (dp_no, dp_yes)
            return memo[key]

        def combine(children: list[int], dchild: int):
            B = budget
            comb = [0] * (B + 1)
            for v in children:
                c_no, c_yes = dfs(v, dchild)
                child_max = [0] * (B + 1)
                for j in range(B + 1):
                    mx = c_no[j]
                    if c_yes[j] > -INF:
                        mx = max(mx, c_yes[j])
                    child_max[j] = mx
                new_comb = [-INF] * (B + 1)
                for p in range(B + 1):
                    for m in range(B - p + 1):
                        new_comb[p + m] = max(new_comb[p + m], comb[p] + child_max[m])
                for j in range(1, B + 1):
                    new_comb[j] = max(new_comb[j], new_comb[j - 1])
                comb = new_comb
            return comb

        if n == 0:
            return 0
        dp_no, dp_yes = dfs(1, 0)
        ans = 0
        for k in range(budget + 1):
            ans = max(ans, dp_no[k])
            if dp_yes[k] > -INF:
                ans = max(ans, dp_yes[k])
        return ans
# @lc code=end