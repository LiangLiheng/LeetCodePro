#
# @lc app=leetcode id=3327 lang=python3
#
# [3327] Check if DFS Strings Are Palindromes
#

# @lc code=start
class Solution:
    def findAnswer(self, parent: List[int], s: str) -> List[bool]:
        n = len(parent)
        adj = [[] for _ in range(n)]
        for i in range(1, n):
            adj[parent[i]].append(i)
        for u in range(n):
            adj[u].sort()
        
        MOD1 = 1000000007
        MOD2 = 1000000009
        BASE1 = 131
        BASE2 = 137
        
        pow1 = [1] * (n + 1)
        pow2 = [1] * (n + 1)
        for i in range(1, n + 1):
            pow1[i] = pow1[i - 1] * BASE1 % MOD1
            pow2[i] = pow2[i - 1] * BASE2 % MOD2
        
        h_fwd = [[0, 0] for _ in range(n)]
        h_rev = [[0, 0] for _ in range(n)]
        sz = [0] * n
        
        def dfs(u):
            children = adj[u]
            total_sz = 1
            hf1, hf2 = 0, 0
            for c in children:
                dfs(c)
                total_sz += sz[c]
                p1 = pow1[sz[c]]
                p2 = pow2[sz[c]]
                hf1 = (hf1 * p1 + h_fwd[c][0]) % MOD1
                hf2 = (hf2 * p2 + h_fwd[c][1]) % MOD2
            ch = ord(s[u]) - ord('a') + 1
            p1 = pow1[1]
            p2 = pow2[1]
            hf1 = (hf1 * p1 + ch) % MOD1
            hf2 = (hf2 * p2 + ch) % MOD2
            h_fwd[u] = [hf1, hf2]
            sz[u] = total_sz
            
            hr1 = ch % MOD1
            hr2 = ch % MOD2
            for c in reversed(children):
                p1 = pow1[sz[c]]
                p2 = pow2[sz[c]]
                hr1 = (hr1 * p1 + h_rev[c][0]) % MOD1
                hr2 = (hr2 * p2 + h_rev[c][1]) % MOD2
            h_rev[u] = [hr1, hr2]
        
        import sys
        sys.setrecursionlimit(100010)
        dfs(0)
        
        answer = [(h_fwd[i][0] == h_rev[i][0] and h_fwd[i][1] == h_rev[i][1]) for i in range(n)]
        return answer
# @lc code=end