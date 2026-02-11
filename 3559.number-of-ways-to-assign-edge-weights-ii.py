#
# @lc app=leetcode id=3559 lang=python3
#
# [3559] Number of Ways to Assign Edge Weights II
#

# @lc code=start
from typing import List
class Solution:
    def assignEdgeWeights(self, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        import sys
        sys.setrecursionlimit(1 << 25)
        MOD = 10**9 + 7
        n = len(edges) + 1
        tree = [[] for _ in range(n + 1)]
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)
        LOG = 20
        parent = [[-1] * (n + 1) for _ in range(LOG)]
        depth = [0] * (n + 1)
        def dfs(u, p):
            parent[0][u] = p
            for v in tree[u]:
                if v != p:
                    depth[v] = depth[u] + 1
                    dfs(v, u)
        dfs(1, -1)
        for k in range(1, LOG):
            for v in range(1, n + 1):
                if parent[k-1][v] != -1:
                    parent[k][v] = parent[k-1][parent[k-1][v]]
        def lca(u, v):
            if depth[u] < depth[v]:
                u, v = v, u
            for k in range(LOG-1, -1, -1):
                if parent[k][u] != -1 and depth[parent[k][u]] >= depth[v]:
                    u = parent[k][u]
            if u == v:
                return u
            for k in range(LOG-1, -1, -1):
                if parent[k][u] != -1 and parent[k][u] != parent[k][v]:
                    u = parent[k][u]
                    v = parent[k][v]
            return parent[0][u]
        def pow2(x):
            res = 1
            base = 2
            while x > 0:
                if x % 2:
                    res = res * base % MOD
                base = base * base % MOD
                x //= 2
            return res
        ans = []
        for u, v in queries:
            if u == v:
                ans.append(0)
                continue
            anc = lca(u, v)
            L = depth[u] + depth[v] - 2 * depth[anc]
            # Verification step: For small L, check pow2(L-1) matches manual calculation
            # For example, if L in (1,2,3), pow2(L-1) should be (1,2,4)
            if L == 0:
                ans.append(0)
            else:
                ans.append(pow2(L-1))
        return ans
# @lc code=end