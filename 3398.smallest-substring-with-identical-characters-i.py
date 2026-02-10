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
            prev_dp = [[INF] * 2 for _ in range(L + 1)]
            for c in range(2):
                cost = (str(c) != s[0])
                prev_dp[1][c] = cost
            for pos in range(1, n):
                curr_dp = [[INF] * 2 for _ in range(L + 1)]
                for r in range(1, L + 1):
                    for pc in range(2):
                        if prev_dp[r][pc] == INF:
                            continue
                        for nc in range(2):
                            cost = (str(nc) != s[pos])
                            nr = r + 1 if nc == pc else 1
                            if nr > L:
                                continue
                            curr_dp[nr][nc] = min(curr_dp[nr][nc], prev_dp[r][pc] + cost)
                prev_dp = curr_dp
            min_flips = min(min(prev_dp[r][0], prev_dp[r][1]) for r in range(1, L + 1))
            return min_flips <= numOps
        
        left, right = 1, n
        while left < right:
            mid = (left + right) // 2
            if can(mid):
                right = mid
            else:
                left = mid + 1
        return left

# @lc code=end