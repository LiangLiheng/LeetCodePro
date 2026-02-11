#
# @lc app=leetcode id=3553 lang=python3
#
# [3553] Minimum Weighted Subgraph With the Required Paths II
#

# @lc code=start
class Solution:
    def minimumWeight(self, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        from collections import defaultdict
        import sys
        sys.setrecursionlimit(1 << 20)
        n = max(max(u, v) for u, v, w in edges) + 1
        tree = defaultdict(list)
        for u, v, w in edges:
            tree[u].append((v, w))
            tree[v].append((u, w))

        LOG = 17  # 2^17 > 1e5
        parent = [[-1] * n for _ in range(LOG)]
        depth = [0] * n
        path_sum = [0] * n

        def dfs(u, p):
            for v, w in tree[u]:
                if v == p:
                    continue
                parent[0][v] = u
                depth[v] = depth[u] + 1
                path_sum[v] = path_sum[u] + w
                dfs(v, u)

        dfs(0, -1)
        for k in range(1, LOG):
            for v in range(n):
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

        def path(u, v):
            l = lca(u, v)
            return path_sum[u] + path_sum[v] - 2 * path_sum[l]

        res = []
        for src1, src2, dest in queries:
            l1 = lca(src1, dest)
            l2 = lca(src2, dest)
            l3 = lca(src1, src2)
            total = path(src1, l3) + path(src2, l3) + path(dest, l3)
            res.append(total)
        return res
# @lc code=end