#
# @lc app=leetcode id=3609 lang=python3
#
# [3609] Minimum Moves to Reach Target in Grid
#

# @lc code=start
from collections import deque

class Solution:
    def minMoves(self, sx: int, sy: int, tx: int, ty: int) -> int:
        visited = set()
        q = deque()
        q.append((tx, ty, 0))
        visited.add((tx, ty))
        while q:
            x, y, dist = q.popleft()
            if x == sx and y == sy:
                return dist
            # Reverse x-add case 1: p >= y, x even
            if x % 2 == 0:
                p = x // 2
                if p >= y and p >= sx and y >= sy and (p, y) not in visited:
                    visited.add((p, y))
                    q.append((p, y, dist + 1))
            # Reverse x-add case 2: p < y
            p = x - y
            if 0 <= p < y and p >= sx and y >= sy and (p, y) not in visited:
                visited.add((p, y))
                q.append((p, y, dist + 1))
            # Reverse y-add case 1: q >= x, y even
            if y % 2 == 0:
                q_ = y // 2
                if q_ >= x and x >= sx and q_ >= sy and (x, q_) not in visited:
                    visited.add((x, q_))
                    q.append((x, q_, dist + 1))
            # Reverse y-add case 2: q < x
            q_ = y - x
            if 0 <= q_ < x and x >= sx and q_ >= sy and (x, q_) not in visited:
                visited.add((x, q_))
                q.append((x, q_, dist + 1))
        return -1
# @lc code=end