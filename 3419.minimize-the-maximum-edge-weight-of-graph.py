#
# @lc app=leetcode id=3419 lang=python3
#
# [3419] Minimize the Maximum Edge Weight of Graph
#

# @lc code=start
from typing import List
from collections import deque

class Solution:
    def minMaxWeight(self, n: int, edges: List[List[int]], threshold: int) -> int:
        if not edges:
            return -1
        weights = sorted(set(w for _, _, w in edges))
        def check(M: int) -> bool:
            incoming = [[] for _ in range(n)]
            for a, b, w in edges:
                if w <= M:
                    incoming[b].append(a)
            visited = [False] * n
            visited[0] = True
            q = deque([0])
            count = 1
            while q:
                cur = q.popleft()
                for prev in incoming[cur]:
                    if not visited[prev]:
                        visited[prev] = True
                        count += 1
                        q.append(prev)
            return count == n
        left, right = 0, len(weights) - 1
        ans = -1
        while left <= right:
            mid = left + (right - left) // 2
            if check(weights[mid]):
                ans = weights[mid]
                right = mid - 1
            else:
                left = mid + 1
        return ans
# @lc code=end