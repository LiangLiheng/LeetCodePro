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
        rev_adj = [[] for _ in range(n)]
        for a, b in invocations:
            adj[a].append(b)
            rev_adj[b].append(a)
        # Find suspicious: reachable from k
        vis = [False] * n
        suspicious = set()
        stack = [k]
        vis[k] = True
        suspicious.add(k)
        while stack:
            u = stack.pop()
            for v in adj[u]:
                if not vis[v]:
                    vis[v] = True
                    suspicious.add(v)
                    stack.append(v)
        # Check if removable
        can_remove = True
        for s in suspicious:
            for c in rev_adj[s]:
                if c not in suspicious:
                    can_remove = False
                    break
            if not can_remove:
                break
        if can_remove:
            res = [i for i in range(n) if i not in suspicious]
        else:
            res = list(range(n))
        return sorted(res)
# @lc code=end