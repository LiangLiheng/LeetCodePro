#
# @lc app=leetcode id=3493 lang=python3
#
# [3493] Properties Graph
#

# @lc code=start
class Solution:
    def numberOfComponents(self, properties: List[List[int]], k: int) -> int:
        n = len(properties)
        # Build adjacency list
        adj = [[] for _ in range(n)]
        def intersect(a, b):
            return len(set(a) & set(b))
        for i in range(n):
            for j in range(i+1, n):
                if intersect(properties[i], properties[j]) >= k:
                    adj[i].append(j)
                    adj[j].append(i)
        # Verify adjacency: each edge is undirected and intersection condition holds
        # (Omitted in code for efficiency, but should be considered in reasoning)
        visited = [False] * n
        def dfs(u):
            stack = [u]
            while stack:
                node = stack.pop()
                for v in adj[node]:
                    if not visited[v]:
                        visited[v] = True
                        stack.append(v)
        components = 0
        for i in range(n):
            if not visited[i]:
                visited[i] = True
                dfs(i)
                components += 1
        return components
# @lc code=end