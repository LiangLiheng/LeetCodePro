#
# @lc app=leetcode id=3553 lang=python3
#
# [3553] Minimum Weighted Subgraph With the Required Paths II
#

# @lc code=start
from typing import List
from collections import deque

class Solution:
    def minimumWeight(self, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        n = len(edges) + 1
        adj = [[] for _ in range(n)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
        LOG = 18
        parent = [[-1] * n for _ in range(LOG)]
        depth = [0] * n
        hop = [0] * n
        # BFS preprocessing
        visited = [False] * n
        q = deque([0])
        visited[0] = True
        parent[0][0] = -1
        hop[0] = 0
        depth[0] = 0
        while q:
            u = q.popleft()
            for v, w in adj[u]:
                if not visited[v]:
                    visited[v] = True
                    parent[0][v] = u
                    hop[v] = hop[u] + 1
                    depth[v] = depth[u] + w
                    q.append(v)
        # Binary lifting table
        for k in range(1, LOG):
            for i in range(n):
                if parent[k - 1][i] != -1:
                    parent[k][i] = parent[k - 1][parent[k - 1][i]]
        def get_lca(u: int, v: int) -> int:
            if hop[u] > hop[v]:
                u, v = v, u
            # Level v to hop[u]
            diff = hop[v] - hop[u]
            k = 0
            while diff > 0:
                if diff & 1:
                    v = parent[k][v]
                diff >>= 1
                k += 1
            if u == v:
                return u
            # Lift both
            for k in range(LOG - 1, -1, -1):
                if parent[k][u] != parent[k][v]:
                    u = parent[k][u]
                    v = parent[k][v]
            return parent[0][u]
        def get_dist(u: int, v: int) -> int:
            l = get_lca(u, v)
            return depth[u] + depth[v] - 2 * depth[l]
        def get_median(a: int, b: int, c: int) -> int:
            l1 = get_lca(a, b)
            l2 = get_lca(a, c)
            l3 = get_lca(b, c)
            d1 = depth[l1]
            d2 = depth[l2]
            d3 = depth[l3]
            if d1 >= d2 and d1 >= d3:
                return l1
            if d2 >= d1 and d2 >= d3:
                return l2
            return l3
        ans = []
        for s1, s2, dest in queries:
            dis1 = get_dist(s1, dest)
            dis2 = get_dist(s2, dest)
            m = get_median(s1, s2, dest)
            dism = get_dist(m, dest)
            ans.append(dis1 + dis2 - dism)
        return ans
# @lc code=end