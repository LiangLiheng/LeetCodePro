#
# @lc app=leetcode id=3534 lang=python3
#
# [3534] Path Existence Queries in a Graph II
#

# @lc code=start
from typing import List, Dict
from collections import deque, defaultdict

class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
    def find(self, x):
        while self.parent[x] != x:
            self.parent[x] = self.parent[self.parent[x]]
            x = self.parent[x]
        return x
    def union(self, x, y):
        xr, yr = self.find(x), self.find(y)
        if xr != yr:
            self.parent[yr] = xr

class Solution:
    def pathExistenceQueries(self, n: int, nums: List[int], maxDiff: int, queries: List[List[int]]) -> List[int]:
        # Step 1: Build adjacency list and DSU
        indexed_nums = sorted((val, idx) for idx, val in enumerate(nums))
        adj = [[] for _ in range(n)]
        dsu = DSU(n)
        l = 0
        for r in range(n):
            while indexed_nums[r][0] - indexed_nums[l][0] > maxDiff:
                l += 1
            for i in range(l, r):
                u, v = indexed_nums[i][1], indexed_nums[r][1]
                adj[u].append(v)
                adj[v].append(u)
                dsu.union(u, v)
        # Step 2: Verify bidirectional edges and DSU components
        for u in range(n):
            for v in adj[u]:
                assert u in adj[v], "Edge missing in adjacency list"
                assert dsu.find(u) == dsu.find(v), "DSU component mismatch"
        # Step 3: Prepare queries and group for batch BFS
        comp = [dsu.find(i) for i in range(n)]
        answer = [-1] * len(queries)
        query_buckets = defaultdict(list)
        for qi, (u, v) in enumerate(queries):
            if u == v:
                answer[qi] = 0
                continue
            if comp[u] != comp[v]:
                answer[qi] = -1
            else:
                query_buckets[(comp[u], u)].append((v, qi))
        # Step 4: Batch BFS for each (component, source)
        for (comp_id, src), targets in query_buckets.items():
            target_set = {v for v, _ in targets}
            qid_map = {v: qi for v, qi in targets}
            visited = [False] * n
            dist = [0] * n
            dq = deque([src])
            visited[src] = True
            found = set()
            while dq and len(found) < len(target_set):
                node = dq.popleft()
                for nei in adj[node]:
                    if not visited[nei]:
                        visited[nei] = True
                        dist[nei] = dist[node] + 1
                        dq.append(nei)
                        if nei in target_set:
                            answer[qid_map[nei]] = dist[nei]
                            found.add(nei)
        # Step 5: (Optional) Reflect if more batching is needed for large numbers of unique queries
        # Step 6: Return results
        return answer
# @lc code=end