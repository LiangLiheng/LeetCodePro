#
# @lc app=leetcode id=3331 lang=python3
#
# [3331] Find Subtree Sizes After Changes
#

# @lc code=start
from typing import List
class Solution:
    def findSubtreeSizes(self, parent: List[int], s: str) -> List[int]:
        n = len(parent)
        # Step 1: Prepare the tree
        tree = [[] for _ in range(n)]
        for i in range(1, n):
            tree[parent[i]].append(i)

        # Step 2: Find new parent for each node
        new_parent = parent[:]
        # For each character, store stack of (node) in current DFS path
        from collections import defaultdict
        char_stack = defaultdict(list)
        def dfs(u):
            char = s[u]
            char_stack[char].append(u)
            for v in tree[u]:
                # Find closest ancestor with same char
                if len(char_stack[char]) > 1:
                    new_parent[v] = char_stack[char][-2]
                else:
                    new_parent[v] = parent[v]
                dfs(v)
            char_stack[char].pop()
        dfs(0)

        # Step 3: Validate new tree structure
        root_count = sum(1 for p in new_parent if p == -1)
        assert root_count == 1, 'Invalid tree: should have exactly one root.'
        # Build visited set to check connectivity
        visited = set()
        def check(u):
            visited.add(u)
            for v in range(n):
                if new_parent[v] == u:
                    if v in visited:
                        raise Exception('Cycle detected')
                    check(v)
        check(new_parent.index(-1))
        assert len(visited) == n, 'Tree not connected after parent change.'

        # Step 4: Build new tree
        new_tree = [[] for _ in range(n)]
        for i in range(1, n):
            new_tree[new_parent[i]].append(i)

        # Step 5: Compute subtree sizes
        sizes = [0] * n
        def compute(u):
            size = 1
            for v in new_tree[u]:
                size += compute(v)
            sizes[u] = size
            return size
        compute(0)
        return sizes
# @lc code=end