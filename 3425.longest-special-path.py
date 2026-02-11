#
# @lc app=leetcode id=3425 lang=python3
#
# [3425] Longest Special Path
#

# @lc code=start
from typing import List, Tuple, Set
from collections import defaultdict

class Solution:
    def longestSpecialPath(self, edges: List[List[int]], nums: List[int]) -> List[int]:
        n = len(nums)
        adj = defaultdict(list)
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))

        result = [0, 1]

        def dfs(node: int, parent: int) -> Tuple[Set[int], int, int]:
            # Returns (unique values set, total length, node count) for the best path starting at node
            best_set = {nums[node]}
            best_len = 0
            best_cnt = 1
            child_paths = []
            for nei, w in adj[node]:
                if nei == parent:
                    continue
                child_set, child_len, child_cnt = dfs(nei, node)
                if nums[node] not in child_set:
                    child_paths.append((child_set, child_len + w, child_cnt + 1))
            # Choose the best child path to extend
            for s, l, c in child_paths:
                if l > best_len or (l == best_len and c < best_cnt):
                    best_set = s | {nums[node]}
                    best_len = l
                    best_cnt = c
            # Update global result
            if best_len > result[0] or (best_len == result[0] and best_cnt < result[1]):
                result[0] = best_len
                result[1] = best_cnt
            return (best_set, best_len, best_cnt)

        dfs(0, -1)
        return result
# @lc code=end