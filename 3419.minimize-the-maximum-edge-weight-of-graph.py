#
# @lc app=leetcode id=3419 lang=python3
#
# [3419] Minimize the Maximum Edge Weight of Graph
#

# @lc code=start
from collections import deque
from typing import List

class Solution:
    def minMaxWeight(self, n: int, edges: List[List[int]], threshold: int) -> int:
        ws = sorted(set(e[2] for e in edges))
        def check(mx: int) -> bool:
            adj = [[] for _ in range(n)]
            for a, b, w in edges:
                if w <= mx:
                    adj[b].append(a)
            vis = [False] * n
            q = deque([0])
            vis[0] = True
            cnt = 1
            while q:
                u = q.popleft()
                for v in adj[u]:
                    if not vis[v]:
                        vis[v] = True
                        cnt += 1
                        q.append(v)
            return cnt == n
        l, r = 0, len(ws) - 1
        ans = -1
        while l <= r:
            m = (l + r) // 2
            if check(ws[m]):
                ans = ws[m]
                r = m - 1
            else:
                l = m + 1
        return ans

# @lc code=end