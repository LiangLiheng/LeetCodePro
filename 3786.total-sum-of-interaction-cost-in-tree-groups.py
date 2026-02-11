#
# @lc app=leetcode id=3786 lang=python3
#
# [3786] Total Sum of Interaction Cost in Tree Groups
#

# @lc code=start
class Solution:
    def interactionCosts(self, n: int, edges: List[List[int]], group: List[int]) -> int:
        adj = [[] for _ in range(n)]
        for a, b in edges:
            adj[a].append(b)
            adj[b].append(a)
        tot = [0] * 21
        for i in range(n):
            tot[group[i]] += 1
        ans = [0]
        def dfs(node, par):
            subtree = [0] * 21
            for nei in adj[node]:
                if nei != par:
                    child_sub = dfs(nei, node)
                    for g in range(1, 21):
                        sz = child_sub[g]
                        ans[0] += sz * (tot[g] - sz)
                        subtree[g] += sz
            subtree[group[node]] += 1
            return subtree
        import sys
        sys.setrecursionlimit(10**5 + 10)
        dfs(0, -1)
        return ans[0]

# @lc code=end