#
# @lc app=leetcode id=3486 lang=python3
#
# [3486] Longest Special Path II
#

# @lc code=start
from collections import defaultdict, Counter
class Solution:
    def longestSpecialPath(self, edges: List[List[int]], nums: List[int]) -> List[int]:
        n = len(nums)
        tree = defaultdict(list)
        for u, v, l in edges:
            tree[u].append((v, l))
            tree[v].append((u, l))

        self.max_len = 0
        self.min_nodes = float('inf')

        # Helper to check the special path constraint
        def is_valid(counter):
            duplicates = 0
            for count in counter.values():
                if count == 2:
                    duplicates += 1
                elif count > 2:
                    return False
            return duplicates <= 1

        def dfs(u, parent, path_counter, cur_len, cur_nodes):
            val = nums[u]
            path_counter[val] += 1

            if is_valid(path_counter):
                if cur_len > self.max_len:
                    self.max_len = cur_len
                    self.min_nodes = cur_nodes
                elif cur_len == self.max_len:
                    self.min_nodes = min(self.min_nodes, cur_nodes)
                for v, l in tree[u]:
                    if v == parent:
                        continue
                    dfs(v, u, path_counter, cur_len + l, cur_nodes + 1)
            # Backtrack
            path_counter[val] -= 1

        dfs(0, -1, Counter(), 0, 1)
        # After traversal, double-check that answer meets constraints
        # (already ensured by is_valid during traversal)
        return [self.max_len, self.min_nodes]
# @lc code=end