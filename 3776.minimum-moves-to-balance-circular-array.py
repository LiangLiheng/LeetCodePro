#
# @lc app=leetcode id=3776 lang=python3
#
# [3776] Minimum Moves to Balance Circular Array
#

# @lc code=start
from typing import List

class Solution:
    def minMoves(self, balance: List[int]) -> int:
        n = len(balance)
        total = sum(balance)
        if total < 0:
            return -1
        if all(x >= 0 for x in balance):
            return 0
        # Find the index with the negative balance
        deficit_idx = -1
        for i, val in enumerate(balance):
            if val < 0:
                deficit_idx = i
                break
        deficit = -balance[deficit_idx]
        # Collect all surplus positions and their values
        surplus = []
        for i, val in enumerate(balance):
            if val > 0:
                # Distance in circular array
                dist = min((i - deficit_idx) % n, (deficit_idx - i) % n)
                surplus.append((dist, i, val))
        surplus.sort()  # process closest first
        moves = 0
        for dist, idx, val in surplus:
            if deficit <= 0:
                break
            take = min(deficit, val)
            moves += take * dist
            deficit -= take
        # Final check: all balances should be non-negative
        if deficit > 0:
            return -1
        return moves
# @lc code=end