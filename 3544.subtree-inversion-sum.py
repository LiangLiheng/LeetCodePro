#
# @lc app=leetcode id=3544 lang=python3
#
# [3544] Subtree Inversion Sum
#

# @lc code=start
from typing import List
from functools import lru_cache

class Solution:
    def subtreeInversionSum(self, edges: List[List[int]], nums: List[int], k: int) -> int:
        n = len(nums)
        adj = [[] for _ in range(n)]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)

        from sys import setrecursionlimit
        setrecursionlimit(100000)

        @lru_cache(maxsize=None)
        def dp(node, parent, dist, sign):
            curr_val = sign * nums[node]
            children = [nei for nei in adj[node] if nei != parent]
            # Option 1: Do not invert at this node
            sum_no_invert = curr_val
            for child in children:
                sum_no_invert += dp(child, node, min(dist+1, k), sign)
            max_sum = sum_no_invert
            # Option 2: Invert at this node if allowed by distance constraint
            if dist >= k:
                sum_invert = -curr_val
                for child in children:
                    sum_invert += dp(child, node, 1, -sign)  # verify update reflects intended meaning
                max_sum = max(max_sum, sum_invert)
            return max_sum

        return dp(0, -1, k, 1)
# @lc code=end