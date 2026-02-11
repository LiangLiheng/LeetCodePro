#
# @lc app=leetcode id=3341 lang=python3
#
# [3341] Find Minimum Time to Reach Last Room I
#

# @lc code=start
from typing import List
import heapq

class Solution:
    def minTimeToReach(self, moveTime: List[List[int]]) -> int:
        n, m = len(moveTime), len(moveTime[0])
        dist = [[float('inf')] * m for _ in range(n)]
        dist[0][0] = 0
        heap = [(0, 0, 0)]  # (current_time, row, col)
        directions = [(-1,0),(1,0),(0,-1),(0,1)]
        while heap:
            t, r, c = heapq.heappop(heap)
            if (r, c) == (n-1, m-1):
                return t
            if t > dist[r][c]:
                continue
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < n and 0 <= nc < m:
                    next_time = max(t + 1, moveTime[nr][nc])
                    if next_time < dist[nr][nc]:
                        dist[nr][nc] = next_time
                        heapq.heappush(heap, (next_time, nr, nc))
        return -1
# @lc code=end