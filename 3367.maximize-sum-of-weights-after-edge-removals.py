#
# @lc app=leetcode id=3367 lang=python3
#
# [3367] Maximize Sum of Weights after Edge Removals
#

# @lc code=start
from typing import List

class Solution:
    def maximizeSumOfWeights(self, edges: List[List[int]], k: int) -> int:
        import sys
        sys.setrecursionlimit(100010)
        n = len(edges) + 1
        adj = [[] for _ in range(n)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
        
        def dfs(u, p):
            gains = []
            total_full = 0
            for v, w in adj[u]:
                if v == p:
                    continue
                f, r = dfs(v, u)
                total_full += f
                gains.append(w + r - f)
            gains.sort(reverse=True)
            gain_max_full = 0
            gain_max_red = 0
            current = 0
            for i in range(len(gains)):
                current += gains[i]
                s = i + 1
                if s <= k:
                    gain_max_full = max(gain_max_full, current)
                if s <= k - 1:
                    gain_max_red = max(gain_max_red, current)
            full = total_full + gain_max_full
            red = total_full + gain_max_red
            return full, red
        
        return dfs(0, -1)[0]
# @lc code=end