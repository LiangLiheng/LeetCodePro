#
# @lc app=leetcode id=3373 lang=python3
#
# [3373] Maximize the Number of Target Nodes After Connecting Trees II
#

# @lc code=start
from typing import List
from collections import deque

class Solution:
    def maxTargetNodes(self, edges1: List[List[int]], edges2: List[List[int]]) -> List[int]:
        n = len(edges1) + 1
        m = len(edges2) + 1
        adj1 = [[] for _ in range(n)]
        for a, b in edges1:
            adj1[a].append(b)
            adj1[b].append(a)
        adj2 = [[] for _ in range(m)]
        for a, b in edges2:
            adj2[a].append(b)
            adj2[b].append(a)

        def compute(adj, N):
            parity = [-1] * N
            q = deque()
            root = 0
            parity[root] = 0
            q.append(root)
            sizes = [0, 0]
            while q:
                u = q.popleft()
                sizes[parity[u]] += 1
                for v in adj[u]:
                    if parity[v] == -1:
                        parity[v] = 1 - parity[u]
                        q.append(v)
            return parity, sizes

        parity1, sizes1 = compute(adj1, n)
        _, sizes2 = compute(adj2, m)
        max_t2 = max(sizes2)
        answer = [0] * n
        for i in range(n):
            p = parity1[i]
            answer[i] = sizes1[p] + max_t2
        return answer
# @lc code=end