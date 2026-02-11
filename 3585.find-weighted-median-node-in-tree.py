#
# @lc app=leetcode id=3585 lang=python3
#
# [3585] Find Weighted Median Node in Tree
#

# @lc code=start
from typing import List
from collections import deque

class Solution:
    def findMedian(self, n: int, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        adj = [[] for _ in range(n)]
        for a, b, w in edges:
            adj[a].append((b, w))
            adj[b].append((a, w))
        
        LOG = 18
        par = [[-1] * n for _ in range(LOG)]
        dep = [0] * n
        level = [0] * n
        
        q = deque([0])
        vis = [False] * n
        vis[0] = True
        par[0][0] = -1
        while q:
            u = q.popleft()
            for v, w in adj[u]:
                if not vis[v]:
                    vis[v] = True
                    par[0][v] = u
                    dep[v] = dep[u] + w
                    level[v] = level[u] + 1
                    q.append(v)
        
        for k in range(1, LOG):
            for i in range(n):
                if par[k - 1][i] != -1:
                    par[k][i] = par[k - 1][par[k - 1][i]]
        
        def get_lca(u: int, v: int) -> int:
            if level[u] > level[v]:
                u, v = v, u
            diff = level[v] - level[u]
            for k in range(LOG):
                if (diff >> k) & 1:
                    v = par[k][v]
            if u == v:
                return u
            for k in range(LOG - 1, -1, -1):
                if par[k][u] != par[k][v]:
                    u = par[k][u]
                    v = par[k][v]
            return par[0][u]
        
        def find_up(u: int, thresh: int) -> int:
            if dep[u] <= thresh:
                return u
            cur = u
            for k in range(LOG - 1, -1, -1):
                anc = par[k][cur]
                if anc != -1 and dep[anc] > thresh:
                    cur = anc
            next_node = par[0][cur]
            return next_node if next_node != -1 else cur
        
        def find_down(v: int, thresh: int) -> int:
            cur = v
            for k in range(LOG - 1, -1, -1):
                anc = par[k][cur]
                if anc != -1 and dep[anc] >= thresh:
                    cur = anc
            return cur
        
        ans = []
        for qu, qv in queries:
            l = get_lca(qu, qv)
            ascent = dep[qu] - dep[l]
            total_w = ascent + dep[qv] - dep[l]
            target = (total_w + 1) // 2
            if ascent >= target:
                th_up = dep[qu] - target
                med = find_up(qu, th_up)
            else:
                prefix_lca = ascent
                th_down = dep[l] + target - prefix_lca
                med = find_down(qv, th_down)
            ans.append(med)
        return ans

# @lc code=end