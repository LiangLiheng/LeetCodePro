#
# @lc app=leetcode id=3544 lang=python3
#
# [3544] Subtree Inversion Sum
#

# @lc code=start
class Solution:
    def subtreeInversionSum(self, edges: List[List[int]], nums: List[int], k: int) -> int:
        n = len(nums)
        adj = [[] for _ in range(n)]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)
        import sys
        sys.setrecursionlimit(50010)
        from functools import lru_cache
        MIN_VAL = - (n * 50001)
        @lru_cache(maxsize=None)
        def dfs(u: int, p: int, par: int, d: int) -> int:
            res = MIN_VAL
            for flip in [0, 1]:
                if flip == 1 and d < k:
                    continue
                sign = 1 if (par + flip) % 2 == 0 else -1
                contrib = nums[u] * sign
                cpar = (par + flip) % 2
                cd = 1 if flip else min(d + 1, k)
                tot_child = 0
                for v in adj[u]:
                    if v != p:
                        tot_child += dfs(v, u, cpar, cd)
                res = max(res, contrib + tot_child)
            return res
        return dfs(0, -1, 0, k)

# @lc code=end