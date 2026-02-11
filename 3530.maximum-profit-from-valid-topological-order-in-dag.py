#
# @lc app=leetcode id=3530 lang=python3
#
# [3530] Maximum Profit from Valid Topological Order in DAG
#

# @lc code=start
from typing import List
class Solution:
    def maxProfit(self, n: int, edges: List[List[int]], score: List[int]) -> int:
        from functools import lru_cache
        # Build a bitmask for prerequisites of each node
        prereq = [0] * n
        for u, v in edges:
            prereq[v] |= (1 << u)

        @lru_cache(None)
        def dp(mask):
            # Base case: all nodes are processed
            if mask == (1 << n) - 1:
                return 0
            res = 0
            pos = bin(mask).count('1') + 1  # Position is 1-based
            for i in range(n):
                # Check if node i is not yet processed
                if not (mask & (1 << i)):
                    # Check if all prerequisites of i are already processed
                    if (prereq[i] & mask) == prereq[i]:
                        # Node i is available to process next
                        next_profit = score[i] * pos + dp(mask | (1 << i))
                        res = max(res, next_profit)
            return res
        return dp(0)
# @lc code=end