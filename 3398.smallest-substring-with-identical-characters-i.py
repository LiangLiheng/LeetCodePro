#
# @lc app=leetcode id=3398 lang=python3
#
# [3398] Smallest Substring With Identical Characters I
#

# @lc code=start
class Solution:
    def minLength(self, s: str, numOps: int) -> int:
        n = len(s)
        def can(L: int) -> bool:
            INF = n + 1
            prev = [[INF] * (L + 1) for _ in range(2)]
            for c in range(2):
                cost = 0 if int(s[0]) == c else 1
                prev[c][1] = cost
            for i in range(1, n):
                curr = [[INF] * (L + 1) for _ in range(2)]
                for pc in range(2):
                    for pk in range(1, L + 1):
                        if prev[pc][pk] == INF:
                            continue
                        for nc in range(2):
                            cost = 0 if int(s[i]) == nc else 1
                            if nc == pc and pk + 1 <= L:
                                nk = pk + 1
                                curr[nc][nk] = min(curr[nc][nk], prev[pc][pk] + cost)
                            elif nc != pc:
                                nk = 1
                                curr[nc][nk] = min(curr[nc][nk], prev[pc][pk] + cost)
                prev = curr
            minf = INF
            for c in range(2):
                for k in range(1, L + 1):
                    minf = min(minf, prev[c][k])
            return minf <= numOps
        left, right = 1, n
        while left < right:
            mid = (left + right) // 2
            if can(mid):
                right = mid
            else:
                left = mid + 1
        return left

# @lc code=end