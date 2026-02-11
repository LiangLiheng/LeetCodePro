#
# @lc app=leetcode id=3538 lang=python3
#
# [3538] Merge Operations for Minimum Travel Time
#

# @lc code=start
from typing import List
from functools import lru_cache

class Solution:
    def minTravelTime(self, l: int, n: int, k: int, position: List[int], time: List[int]) -> int:
        positions = position[:]
        times = time[:]

        @lru_cache(maxsize=None)
        def dp(pos_tuple, time_tuple, merges_left):
            pos = list(pos_tuple)
            t = list(time_tuple)
            length = len(pos)
            if merges_left == 0:
                # Compute total time
                total = 0
                for i in range(length - 1):
                    dist = pos[i+1] - pos[i]
                    total += dist * t[i]
                return total
            min_time = float('inf')
            # Try all possible merges (not at the first or last sign)
            for i in range(1, length - 1):
                # Merge sign at i with i+1, remove i
                new_pos = pos[:i] + pos[i+1:]
                new_t = t[:i-1] + [t[i-1] + t[i]] + t[i+1:]
                # General validation: check for correct lengths and index validity
                if len(new_pos) != length - 1 or len(new_t) != length - 1:
                    continue
                cand = dp(tuple(new_pos), tuple(new_t), merges_left - 1)
                if cand < min_time:
                    min_time = cand
            return min_time

        result = dp(tuple(positions), tuple(times), k)
        # Final verification: ensure result is an integer and non-negative
        assert isinstance(result, int) or isinstance(result, float)
        assert result >= 0
        return result
# @lc code=end