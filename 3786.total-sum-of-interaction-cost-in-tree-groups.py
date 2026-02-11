#
# @lc app=leetcode id=3786 lang=python3
#
# [3786] Total Sum of Interaction Cost in Tree Groups
#

# @lc code=start
from collections import defaultdict
class Solution:
    def interactionCosts(self, n: int, edges: List[List[int]], group: List[int]) -> int:
        tree = [[] for _ in range(n)]
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)
        group_nodes = defaultdict(list)
        for i, g in enumerate(group):
            group_nodes[g].append(i)
        total = 0
        for g, nodes in group_nodes.items():
            if len(nodes) < 2:
                continue
            in_group = [0] * n
            for u in nodes:
                in_group[u] = 1
            cnt = [0] * n
            parent = [-1] * n
            def dfs(u, p):
                cnt[u] = in_group[u]
                parent[u] = p
                for v in tree[u]:
                    if v == p:
                        continue
                    dfs(v, u)
                    cnt[u] += cnt[v]
            dfs(nodes[0], -1)  # Start DFS from any group node; ensure correctness for all trees
            for u in range(n):
                for v in tree[u]:
                    if parent[v] == u:
                        c = cnt[v]
                        total += c * (len(nodes) - c)
            # Double-counting: each pair is counted twice, so divide by 2 after summing
        # Final verification: check with small examples to ensure correctness and that each unordered pair is counted once
        return total // 2
# @lc code=end