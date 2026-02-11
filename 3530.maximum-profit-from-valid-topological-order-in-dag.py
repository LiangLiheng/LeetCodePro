#
# @lc app=leetcode id=3530 lang=python3
#
# [3530] Maximum Profit from Valid Topological Order in DAG
#

# @lc code=start
class Solution:
    def maxProfit(self, n: int, edges: List[List[int]], score: List[int]) -> int:
        pred_mask = [0] * n
        for u, v in edges:
            pred_mask[v] |= (1 << u)
        N = 1 << n
        memo = [-1] * N
        popcount = [0] * N
        for i in range(N):
            popcount[i] = popcount[i >> 1] + (i & 1)
        def dfs(mask):
            if popcount[mask] == n:
                return 0
            if memo[mask] != -1:
                return memo[mask]
            pos = popcount[mask] + 1
            res = 0
            for v in range(n):
                if (mask & (1 << v)) != 0:
                    continue
                if (pred_mask[v] & mask) == pred_mask[v]:
                    sub = dfs(mask | (1 << v))
                    res = max(res, score[v] * pos + sub)
            memo[mask] = res
            return res
        return dfs(0)
# @lc code=end