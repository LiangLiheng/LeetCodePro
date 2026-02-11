#
# @lc app=leetcode id=3515 lang=python3
#
# [3515] Shortest Path in a Weighted Tree
#

# @lc code=start
class Solution:
    def treeQueries(self, n: int, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        from collections import defaultdict
        
        tree = defaultdict(list)
        for u, v, w in edges:
            tree[u].append((v, w))
            tree[v].append((u, w))
        
        parent = [0] * (n + 1)
        depth = [0] * (n + 1)
        dist = [0] * (n + 1)
        def dfs(u, p):
            for v, w in tree[u]:
                if v == p:
                    continue
                parent[v] = u
                depth[v] = depth[u] + 1
                dist[v] = dist[u] + w
                dfs(v, u)
        dfs(1, 0)
        
        in_time = [0] * (n + 1)
        out_time = [0] * (n + 1)
        time = [0]
        def euler(u, p):
            time[0] += 1
            in_time[u] = time[0]
            for v, _ in tree[u]:
                if v == p:
                    continue
                euler(v, u)
            out_time[u] = time[0]
        euler(1, 0)
        
        class BIT:
            def __init__(self, size):
                self.N = size + 2
                self.tree = [0] * (self.N)
            def update(self, x, delta):
                while x < self.N:
                    self.tree[x] += delta
                    x += (x & -x)
            def query(self, x):
                res = 0
                while x > 0:
                    res += self.tree[x]
                    x -= (x & -x)
                return res
            def range_add(self, l, r, delta):
                self.update(l, delta)
                self.update(r + 1, -delta)
        bit = BIT(n + 2)
        edge_weights = {}
        for u, v, w in edges:
            edge_weights[(u, v)] = edge_weights[(v, u)] = w
        ans = []
        for q in queries:
            if q[0] == 1:
                _, u, v, w_new = q
                if depth[u] > depth[v]:
                    child = u
                else:
                    child = v
                w_old = edge_weights[(u, v)]
                delta = w_new - w_old
                bit.range_add(in_time[child], out_time[child], delta)
                edge_weights[(u, v)] = edge_weights[(v, u)] = w_new
            elif q[0] == 2:
                _, x = q
                res = dist[x] + bit.query(in_time[x])
                ans.append(res)
        return ans
# @lc code=end