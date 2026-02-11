#
# @lc app=leetcode id=3604 lang=python3
#
# [3604] Minimum Time to Reach Destination in Directed Graph
#

# @lc code=start
from typing import List
import heapq
from collections import defaultdict

class Solution:
    def minTime(self, n: int, edges: List[List[int]]) -> int:
        graph = defaultdict(list)
        for u, v, s, e in edges:
            graph[u].append((v, s, e))
        # Earliest arrival time at each node
        arrival = [float('inf')] * n
        arrival[0] = 0
        # Heap elements: (current_time, node)
        heap = [(0, 0)]
        while heap:
            time, node = heapq.heappop(heap)
            if node == n - 1:
                return time
            if time > arrival[node]:
                continue
            for neighbor, start, end in graph[node]:
                # Wait until max(time, start) to use the edge
                if time > end:
                    continue
                depart_time = max(time, start)
                if depart_time > end:
                    continue
                arrive_time = depart_time + 1
                if arrive_time < arrival[neighbor]:
                    arrival[neighbor] = arrive_time
                    heapq.heappush(heap, (arrive_time, neighbor))
        return -1
# @lc code=end