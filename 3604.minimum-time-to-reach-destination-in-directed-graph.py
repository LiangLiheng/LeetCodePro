#
# @lc app=leetcode id=3604 lang=python3
#
# [3604] Minimum Time to Reach Destination in Directed Graph
#

# @lc code=start
from collections import defaultdict
import heapq
from typing import List

class Solution:
    def minTime(self, n: int, edges: List[List[int]]) -> int:
        graph = defaultdict(list)
        for u, v, start, end in edges:
            graph[u].append((v, start, end))
        
        INF = 10**18 + 5
        dist = [INF] * n
        dist[0] = 0
        pq = [(0, 0)]  # (time, node)
        
        while pq:
            time, u = heapq.heappop(pq)
            if time > dist[u]:
                continue
            for v, s, e in graph[u]:
                depart = max(time, s)
                if depart <= e:
                    arrival = depart + 1
                    if arrival < dist[v]:
                        dist[v] = arrival
                        heapq.heappush(pq, (arrival, v))
        
        return dist[n-1] if dist[n-1] < INF else -1

# @lc code=end