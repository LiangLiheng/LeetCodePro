#
# @lc app=leetcode id=3562 lang=python3
#
# [3562] Maximum Profit from Trading Stocks with Discounts
#

# @lc code=start
from typing import List
import math

class Solution:
    def maxProfit(self, n: int, present: List[int], future: List[int], hierarchy: List[List[int]], budget: int) -> int:
        from collections import defaultdict
        
        # Build tree from the hierarchy
        tree = [[] for _ in range(n)]
        parent = [-1] * n
        for u, v in hierarchy:
            tree[u-1].append(v-1)
            parent[v-1] = u-1
        root = 0  # CEO is always node 0
        
        # DP function: returns two arrays, dp0, dp1 per node
        # dp0[b]: max profit with budget b, boss did NOT buy
        # dp1[b]: max profit with budget b, boss DID buy
        def dfs(u):
            dp0 = [0] + [-math.inf] * budget
            dp1 = [0] + [-math.inf] * budget
            cost_nodisc = present[u]
            profit_nodisc = future[u] - cost_nodisc
            cost_disc = present[u] // 2
            profit_disc = future[u] - cost_disc
            for v in tree[u]:
                child_dp0, child_dp1 = dfs(v)
                ndp0 = [-math.inf] * (budget+1)
                ndp1 = [-math.inf] * (budget+1)
                for b in range(budget+1):
                    if dp0[b] != -math.inf:
                        for cb in range(budget-b+1):
                            if child_dp0[cb] != -math.inf:
                                ndp0[b+cb] = max(ndp0[b+cb], dp0[b] + child_dp0[cb])
                for b in range(budget+1):
                    if dp1[b] != -math.inf:
                        for cb in range(budget-b+1):
                            if child_dp1[cb] != -math.inf:
                                ndp1[b+cb] = max(ndp1[b+cb], dp1[b] + child_dp1[cb])
                dp0 = ndp0
                dp1 = ndp1
            for b in range(budget, cost_nodisc-1, -1):
                if dp0[b-cost_nodisc] != -math.inf:
                    dp0[b] = max(dp0[b], dp0[b-cost_nodisc] + profit_nodisc)
            for b in range(budget, cost_disc-1, -1):
                if dp1[b-cost_disc] != -math.inf:
                    dp1[b] = max(dp1[b], dp1[b-cost_disc] + profit_disc)
            return dp0, dp1
        dp0, dp1 = dfs(root)
        ans = 0
        for b in range(budget+1):
            ans = max(ans, dp0[b], dp1[b])
        return ans
# @lc code=end