#
# @lc app=leetcode id=3341 lang=python3
#
# [3341] Find Minimum Time to Reach Last Room I
#

# @lc code=start
class Solution:
    def minTimeToReach(self, moveTime: List[List[int]]) -> int:
        import heapq
        n, m = len(moveTime), len(moveTime[0])
        INF = 10**18 + 5
        dist = [[INF] * m for _ in range(n)]
        dist[0][0] = 0
        pq = [(0, 0, 0)]  # time, row, col
        dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        while pq:
            time, i, j = heapq.heappop(pq)
            if time > dist[i][j]:
                continue
            for di, dj in dirs:
                ni, nj = i + di, j + dj
                if 0 <= ni < n and 0 <= nj < m:
                    new_time = max(time, moveTime[ni][nj]) + 1
                    if new_time < dist[ni][nj]:
                        dist[ni][nj] = new_time
                        heapq.heappush(pq, (new_time, ni, nj))
        return dist[n-1][m-1]

# @lc code=end