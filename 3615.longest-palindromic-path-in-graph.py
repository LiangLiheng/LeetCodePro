#
# @lc app=leetcode id=3615 lang=python3
#
# [3615] Longest Palindromic Path in Graph
#

# @lc code=start
from typing import List
from functools import lru_cache

class Solution:
    def maxLen(self, n: int, edges: List[List[int]], label: str) -> int:
        adj = [[] for _ in range(n)]
        for a, b in edges:
            adj[a].append(b)
            adj[b].append(a)
        popcount = [0] * (1 << n)
        for i in range(1 << n):
            popcount[i] = popcount[i >> 1] + (i & 1)
        @lru_cache(maxsize=None)
        def dfs(u: int, v: int, mask: int) -> int:
            ans = popcount[mask]
            for x in adj[u]:
                if (mask & (1 << x)) == 0:
                    for y in adj[v]:
                        if x != y and (mask & (1 << y)) == 0 and label[x] == label[y]:
                            new_mask = mask | (1 << x) | (1 << y)
                            ans = max(ans, dfs(x, y, new_mask))
            return ans
        max_len = 1
        for i in range(n):
            max_len = max(max_len, dfs(i, i, 1 << i))
            for j in adj[i]:
                if label[i] == label[j]:
                    msk = (1 << i) | (1 << j)
                    max_len = max(max_len, dfs(i, j, msk))
        return max_len
# @lc code=end