#
# @lc app=leetcode id=3327 lang=python3
#
# [3327] Check if DFS Strings Are Palindromes
#

# @lc code=start
from typing import List
class Solution:
    def findAnswer(self, parent: List[int], s: str) -> List[bool]:
        n = len(parent)
        adj = [[] for _ in range(n)]
        for i in range(1, n):
            adj[parent[i]].append(i)
        for i in range(n):
            adj[i].sort()
        MOD1 = 1000000007
        MOD2 = 1000000009
        BASE1 = 131
        BASE2 = 137
        pows1 = [1] * (n + 1)
        for i in range(1, n + 1):
            pows1[i] = pows1[i - 1] * BASE1 % MOD1
        pows2 = [1] * (n + 1)
        for i in range(1, n + 1):
            pows2[i] = pows2[i - 1] * BASE2 % MOD2
        lens = [0] * n
        hf1 = [0] * n
        hf2 = [0] * n
        hr1 = [0] * n
        hr2 = [0] * n
        import sys
        sys.setrecursionlimit(100010)
        def dfs(u):
            childs = adj[u]
            for v in childs:
                dfs(v)
            lens[u] = 1
            for v in childs:
                lens[u] += lens[v]
            su = ord(s[u]) - ord('a') + 1
            # compute hf
            cur_hf1 = su % MOD1
            cur_hf2 = su % MOD2
            p1 = pows1[1]
            p2 = pows2[1]
            for v in reversed(childs):
                cur_hf1 = (hf1[v] * p1 + cur_hf1) % MOD1
                cur_hf2 = (hf2[v] * p2 + cur_hf2) % MOD2
                p1 = (p1 * pows1[lens[v]]) % MOD1
                p2 = (p2 * pows2[lens[v]]) % MOD2
            hf1[u] = cur_hf1
            hf2[u] = cur_hf2
            # compute hr
            if not childs:
                hr1[u] = su % MOD1
                hr2[u] = su % MOD2
            else:
                cur_hr1 = hr1[childs[0]]
                cur_hr2 = hr2[childs[0]]
                p1 = pows1[lens[childs[0]]]
                p2 = pows2[lens[childs[0]]]
                for i in range(1, len(childs)):
                    v = childs[i]
                    cur_hr1 = (hr1[v] * p1 + cur_hr1) % MOD1
                    cur_hr2 = (hr2[v] * p2 + cur_hr2) % MOD2
                    p1 = (p1 * pows1[lens[v]]) % MOD1
                    p2 = (p2 * pows2[lens[v]]) % MOD2
                hr1[u] = (su * p1 + cur_hr1) % MOD1
                hr2[u] = (su * p2 + cur_hr2) % MOD2
        dfs(0)
        ans = [False] * n
        for i in range(n):
            if hf1[i] == hr1[i] and hf2[i] == hr2[i]:
                ans[i] = True
        return ans

# @lc code=end