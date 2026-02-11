#
# @lc app=leetcode id=3538 lang=python3
#
# [3538] Merge Operations for Minimum Travel Time
#

# @lc code=start
from typing import List
class Solution:
    def minTravelTime(self, l: int, n: int, k: int, position: List[int], time: List[int]) -> int:
        INF = 10**18
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + time[i]
        dp = [[[INF] * 101 for _ in range(k + 1)] for _ in range(n)]
        dp[0][0][time[0]] = 0
        for i in range(n):
            for j in range(k + 1):
                for t in range(101):
                    if dp[i][j][t] == INF:
                        continue
                    for nxt in range(i + 1, n):
                        merges_add = nxt - i - 1
                        new_j = j + merges_add
                        if new_j > k:
                            break
                        dist = position[nxt] - position[i]
                        cost_add = dist * t
                        sum_int = prefix[nxt] - prefix[i + 1]
                        new_t = time[nxt] + sum_int
                        if new_t > 100:
                            continue
                        new_cost = dp[i][j][t] + cost_add
                        if new_cost < dp[nxt][new_j][new_t]:
                            dp[nxt][new_j][new_t] = new_cost
        ans = INF
        for t in range(101):
            ans = min(ans, dp[n-1][k][t])
        return ans
# @lc code=end