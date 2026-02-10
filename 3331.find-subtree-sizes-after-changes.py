#
# @lc app=leetcode id=3331 lang=python3
#
# [3331] Find Subtree Sizes After Changes
#

# @lc code=start
from typing import List
from collections import deque

class Solution:
    def findSubtreeSizes(self, parent: List[int], s: str) -> List[int]:
        n = len(parent)
        adj = [[] for _ in range(n)]
        for i in range(1, n):
            adj[parent[i]].append(i)
        new_parent = parent[:]
        last_pos = [-1] * 26
        stack = []
        # Initialize root
        root_c = ord(s[0]) - ord('a')
        old_last = last_pos[root_c]
        last_pos[root_c] = 0
        stack.append((0, 0, old_last))
        while stack:
            node, child_idx, my_old = stack[-1]
            if child_idx < len(adj[node]):
                child = adj[node][child_idx]
                stack[-1] = (node, child_idx + 1, my_old)
                child_c = ord(s[child]) - ord('a')
                if last_pos[child_c] != -1:
                    new_parent[child] = last_pos[child_c]
                child_old = last_pos[child_c]
                last_pos[child_c] = child
                stack.append((child, 0, child_old))
            else:
                node_c = ord(s[node]) - ord('a')
                last_pos[node_c] = my_old
                stack.pop()
        # Build new_adj
        new_adj = [[] for _ in range(n)]
        for i in range(1, n):
            new_adj[new_parent[i]].append(i)
        # Compute sizes bottom-up
        pending = [len(new_adj[i]) for i in range(n)]
        ans = [1] * n
        q = deque(i for i in range(n) if pending[i] == 0)
        new_parent[0] = -1
        while q:
            node = q.popleft()
            p = new_parent[node]
            if p != -1:
                ans[p] += ans[node]
                pending[p] -= 1
                if pending[p] == 0:
                    q.append(p)
        return ans

# @lc code=end