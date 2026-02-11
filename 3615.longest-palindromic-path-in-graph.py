#
# @lc app=leetcode id=3615 lang=python3
#
# [3615] Longest Palindromic Path in Graph
#

# @lc code=start
from typing import List
from collections import defaultdict

class Solution:
    def maxLen(self, n: int, edges: List[List[int]], label: str) -> int:
        adj = defaultdict(list)
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)

        def is_palindrome(s):
            return s == s[::-1]

        maxlen = 1
        memo = dict()
        
        def dfs(node, visited, path):
            nonlocal maxlen
            state = (node, visited)
            if state in memo and memo[state] >= len(path):
                return
            memo[state] = len(path)
            if is_palindrome(path):
                maxlen = max(maxlen, len(path))
            # Prune if remaining nodes + len(path) <= maxlen
            if len(path) + (n - bin(visited).count('1')) <= maxlen:
                return
            for nei in adj[node]:
                if not (visited & (1 << nei)):
                    dfs(nei, visited | (1 << nei), path + label[nei])

        for start in range(n):
            dfs(start, 1 << start, label[start])
        return maxlen
# @lc code=end