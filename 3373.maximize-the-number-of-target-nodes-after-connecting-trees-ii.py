#
# @lc app=leetcode id=3373 lang=python3
#
# [3373] Maximize the Number of Target Nodes After Connecting Trees II
#

# @lc code=start
class Solution:
    def maxTargetNodes(self, edges1: List[List[int]], edges2: List[List[int]]) -> List[int]:
        from collections import deque

        def build_adj(edges, size):
            adj = [[] for _ in range(size)]
            for a, b in edges:
                adj[a].append(b)
                adj[b].append(a)
            return adj

        def compute_sizes(adj):
            n = len(adj)
            color = [-1] * n
            sz = [0, 0]
            q = deque([0])
            color[0] = 0
            sz[0] += 1
            while q:
                u = q.popleft()
                for v in adj[u]:
                    if color[v] == -1:
                        color[v] = 1 - color[u]
                        sz[color[v]] += 1
                        q.append(v)
            return color, sz[0], sz[1]

        n = len(edges1) + 1
        m = len(edges2) + 1
        adj1 = build_adj(edges1, n)
        color1, size0_1, size1_1 = compute_sizes(adj1)
        adj2 = build_adj(edges2, m)
        _, size0_2, size1_2 = compute_sizes(adj2)
        extra = max(size0_2, size1_2)
        ans = [0] * n
        for i in range(n):
            if color1[i] == 0:
                ans[i] = size0_1 + extra
            else:
                ans[i] = size1_1 + extra
        return ans

# @lc code=end