#
# @lc app=leetcode id=3310 lang=python3
#
# [3310] Remove Methods From Project
#

# @lc code=start
from typing import List

class Solution:
    def remainingMethods(self, n: int, k: int, invocations: List[List[int]]) -> List[int]:
        adj = [[] for _ in range(n)]
        for a, b in invocations:
            adj[a].append(b)
        
        # Iterative DFS: visited marks suspicious (reachable from k including k)
        visited = [False] * n
        stack = [k]
        visited[k] = True
        while stack:
            node = stack.pop()
            for nei in adj[node]:
                if not visited[nei]:
                    visited[nei] = True
                    stack.append(nei)
        
        # Check no external invocation to suspicious
        can_remove = True
        for a, b in invocations:
            if not visited[a] and visited[b]:
                can_remove = False
                break
        
        if can_remove:
            remaining = [i for i in range(n) if not visited[i]]
        else:
            remaining = list(range(n))
        return remaining
# @lc code=end