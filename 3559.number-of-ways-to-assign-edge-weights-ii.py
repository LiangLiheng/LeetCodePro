#
# @lc app=leetcode id=3559 lang=python3
#
# [3559] Number of Ways to Assign Edge Weights II
#

# @lc code=start
from typing import List
from collections import deque

class Solution:
    def assignEdgeWeights(self, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        n = len(edges) + 1
        MOD = 10**9 + 7
        adj = [[] for _ in range(n + 1)]
        for a, b in edges:
            adj[a].append(b)
            adj[b].append(a)
        LOG = 18
        parent = [[0] * (n + 1) for _ in range(LOG)]
        depth = [0] * (n + 1)
        q = deque([1])
        vis = [False] * (n + 1)
        vis[1] = True
        parent[0][1] = 1
        while q:
            u = q.popleft()
            for v in adj[u]:
                if not vis[v]:
                    vis[v] = True
                    depth[v] = depth[u] + 1
                    parent[0][v] = u
                    q.append(v)
        for k in range(1, LOG):
            for i in range(1, n + 1):
                parent[k][i] = parent[k - 1][parent[k - 1][i]]
        def lca(u: int, v: int) -> int:
            if depth[u] > depth[v]:
                u, v = v, u
            diff = depth[v] - depth[u]
            for k in range(LOG):
                if (diff >> k) & 1:
                    v = parent[k][v]
            if u == v:
                return u
            for k in range(LOG - 1, -1, -1):
                if parent[k][u] != parent[k][v]:
                    u = parent[k][u]
                    v = parent[k][v]
            return parent[0][u]
        answer = []
        for qu, qv in queries:
            if qu == qv:
                answer.append(0)
                continue
            l = lca(qu, qv)
            dist = depth[qu] + depth[qv] - 2 * depth[l]
            ways = pow(2, dist - 1, MOD)
            answer.append(ways)
        return answer
# @lc code=end