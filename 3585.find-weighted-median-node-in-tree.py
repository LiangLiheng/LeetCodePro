#
# @lc app=leetcode id=3585 lang=python3
#
# [3585] Find Weighted Median Node in Tree
#

# @lc code=start
class Solution:
    def findMedian(self, n: int, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        from collections import defaultdict
        import math
        
        # Build adjacency list with weights
        tree = defaultdict(list)
        for u, v, w in edges:
            tree[u].append((v, w))
            tree[v].append((u, w))
        
        LOG = math.ceil(math.log2(n)) + 1
        parent = [[-1]*n for _ in range(LOG)]
        depth = [0]*n
        up_weight = [0]*n  # distance from root
        parent_edge = [0]*n  # edge weight from parent

        def dfs(u, p):
            for v, w in tree[u]:
                if v != p:
                    parent[0][v] = u
                    depth[v] = depth[u]+1
                    up_weight[v] = up_weight[u]+w
                    parent_edge[v] = w
                    dfs(v,u)
        dfs(0,-1)

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

        ans = []
        for u, v in queries:
            x = lca(u,v)
            total = up_weight[u] + up_weight[v] - 2*up_weight[x]
            half = total/2
            # Reconstruct the path from u to v via LCA, as a list of nodes
            path = []
            node = u
            up_nodes = []
            while node != x:
                up_nodes.append(node)
                node = parent[0][node]
            up_nodes.append(x)
            down_nodes = []
            node = v
            tmp = []
            while node != x:
                tmp.append(node)
                node = parent[0][node]
            down_nodes = tmp[::-1]
            full_path = up_nodes + down_nodes
            # Traverse the path, summing edge weights
            curr_sum = 0
            for idx in range(len(full_path)):
                if idx == 0:
                    if curr_sum >= half:
                        ans.append(full_path[idx])
                        break
                else:
                    # Edge from full_path[idx-1] to full_path[idx]
                    prev = full_path[idx-1]
                    curr = full_path[idx]
                    # Find the edge weight
                    # Since it's a tree, parent[0][curr] == prev or parent[0][prev] == curr
                    if parent[0][curr] == prev:
                        w = parent_edge[curr]
                    else:
                        w = parent_edge[prev]
                    curr_sum += w
                    if curr_sum >= half:
                        ans.append(curr)
                        break
        return ans
# @lc code=end