#
# @lc app=leetcode id=3710 lang=python3
#
# [3710] Maximum Partition Factor
#

# @lc code=start
from collections import deque

class Solution:
    def maxPartitionFactor(self, points: List[List[int]]) -> int:
        n = len(points)
        if n == 2:
            return 0
        
        def check(D: int) -> bool:
            adj = [[] for _ in range(n)]
            for i in range(n):
                for j in range(i + 1, n):
                    dx = abs(points[i][0] - points[j][0])
                    dy = abs(points[i][1] - points[j][1])
                    dist = dx + dy
                    if dist < D:
                        adj[i].append(j)
                        adj[j].append(i)
            
            colors = [-1] * n
            
            def bfs(start: int) -> bool:
                from collections import deque
                q = deque([start])
                colors[start] = 0
                while q:
                    u = q.popleft()
                    for v in adj[u]:
                        if colors[v] == -1:
                            colors[v] = 1 - colors[u]
                            q.append(v)
                        elif colors[v] == colors[u]:
                            return False
                return True
            
            for i in range(n):
                if colors[i] == -1:
                    if not bfs(i):
                        return False
            return True
        
        lo, hi = 0, 400000001
        while lo < hi:
            mid = (lo + hi + 1) // 2
            if check(mid):
                lo = mid
            else:
                hi = mid - 1
        return lo

# @lc code=end