#
# @lc app=leetcode id=3594 lang=python3
#
# [3594] Minimum Time to Transport All Individuals
#

# @lc code=start
from typing import List
from collections import deque
import math

class Solution:
    def minTime(self, n: int, k: int, m: int, time: List[int], mul: List[float]) -> float:
        if k == 1 and n > 1:
            return -1.0
        ALL = (1 << n) - 1
        visited = {}  # (mask, stage, boat_side) -> minimal time
        queue = deque()
        queue.append((0.0, 0, 0, 0))
        visited[(0, 0, 0)] = 0.0
        res = float('inf')
        from itertools import combinations
        while queue:
            total_time, mask, stage, boat_side = queue.popleft()
            if mask == ALL and boat_side == 1:
                res = min(res, total_time)
                continue
            if boat_side == 0:
                remaining = [i for i in range(n) if not (mask & (1 << i))]
                for group_size in range(1, min(k, len(remaining)) + 1):
                    for group in combinations(remaining, group_size):
                        next_mask = mask
                        max_time = 0
                        for i in group:
                            next_mask |= 1 << i
                            max_time = max(max_time, time[i])
                        crossing_time = max_time * mul[stage]
                        advance = int(math.floor(crossing_time)) % m
                        next_stage = (stage + advance) % m
                        key = (next_mask, next_stage, 1)
                        next_total_time = total_time + crossing_time
                        if (key not in visited) or (visited[key] > next_total_time):
                            visited[key] = next_total_time
                            queue.append((next_total_time, next_mask, next_stage, 1))
            else:
                if mask == ALL:
                    continue
                at_dest = [i for i in range(n) if (mask & (1 << i))]
                for r in at_dest:
                    return_time = time[r] * mul[stage]
                    advance = int(math.floor(return_time)) % m
                    next_stage = (stage + advance) % m
                    next_mask = mask & (~(1 << r))
                    key = (next_mask, next_stage, 0)
                    next_total_time = total_time + return_time
                    if (key not in visited) or (visited[key] > next_total_time):
                        visited[key] = next_total_time
                        queue.append((next_total_time, next_mask, next_stage, 0))
        return res if res != float('inf') else -1.0
# @lc code=end