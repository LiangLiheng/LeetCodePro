#
# @lc app=leetcode id=3331 lang=python3
#
# [3331] Find Subtree Sizes After Changes
#

# @lc code=start
class Solution:
    def findSubtreeSizes(self, parent: List[int], s: str) -> List[int]:
        import sys
        sys.setrecursionlimit(100010)
        n = len(parent)
        orig_adj = [[] for _ in range(n)]
        for i in range(1, n):
            orig_adj[parent[i]].append(i)
        new_parent = parent[:]
        char_to_node = {}
        def update_parent(node):
            if node != 0 and s[node] in char_to_node:
                new_parent[node] = char_to_node[s[node]]
            prev = char_to_node.get(s[node], None)
            char_to_node[s[node]] = node
            for child in orig_adj[node]:
                update_parent(child)
            if prev is None:
                del char_to_node[s[node]]
            else:
                char_to_node[s[node]] = prev
        update_parent(0)
        new_adj = [[] for _ in range(n)]
        for i in range(1, n):
            new_adj[new_parent[i]].append(i)
        ans = [0] * n
        def compute_size(node):
            sz = 1
            for child in new_adj[node]:
                sz += compute_size(child)
            ans[node] = sz
            return sz
        compute_size(0)
        return ans
# @lc code=end