#
# @lc app=leetcode id=3534 lang=python3
#
# [3534] Path Existence Queries in a Graph II
#

# @lc code=start
class Solution:
    def pathExistenceQueries(self, n: int, nums: list[int], maxDiff: int, queries: list[list[int]]) -> list[int]:
        nodes = sorted(range(n), key=lambda i: nums[i])
        pos = [0] * n
        for p in range(n):
            pos[nodes[p]] = p
        # Compute right_win[p]: farthest right position in 1 hop
        right_win = [0] * n
        j = 0
        for p in range(n):
            while j < n and nums[nodes[j]] <= nums[nodes[p]] + maxDiff:
                j += 1
            right_win[p] = j - 1
        # Binary lifting jump table: jump[p][k] = position after 2^k max-right hops from p
        LOG = 18
        jump = [[0] * LOG for _ in range(n)]
        for p in range(n):
            jump[p][0] = right_win[p]
        for k in range(1, LOG):
            for p in range(n):
                mid = jump[p][k - 1]
                jump[p][k] = jump[mid][k - 1]
        # Compute comp_right[p]: rightmost position in same component as p
        comp_right = [-1] * n
        i = 0
        while i < n:
            j = i
            while j + 1 < n and nums[nodes[j + 1]] - nums[nodes[j]] <= maxDiff:
                j += 1
            for p in range(i, j + 1):
                comp_right[p] = j
            i = j + 1
        # Functions for queries
        def compute_pos(start: int, dd: int) -> int:
            cur = start
            k = 0
            d = dd
            while d > 0:
                if d & 1:
                    cur = jump[cur][k]
                d >>= 1
                k += 1
                if k >= LOG:
                    break
            return cur
        answer = []
        for qu, qv in queries:
            pu = pos[qu]
            pv = pos[qv]
            if pu > pv:
                pu, pv = pv, pu
            if comp_right[pu] < pv:
                answer.append(-1)
                continue
            # Binary search minimal d
            lo = 0
            hi = n
            while lo < hi:
                mid = (lo + hi) // 2
                if compute_pos(pu, mid) >= pv:
                    hi = mid
                else:
                    lo = mid + 1
            answer.append(lo)
        return answer

# @lc code=end