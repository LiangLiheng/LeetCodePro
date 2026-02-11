#
# @lc app=leetcode id=3414 lang=python3
#
# [3414] Maximum Score of Non-overlapping Intervals
#

# @lc code=start
from typing import List
import bisect

class Solution:
    def maximumWeight(self, intervals: List[List[int]]) -> List[int]:
        n = len(intervals)
        # Append original indices to each interval
        intervals = [interval + [i] for i, interval in enumerate(intervals)]
        # Sort by end time, then by index for lex order
        intervals.sort(key=lambda x: (x[1], x[3]))
        ends = [itv[1] for itv in intervals]
        # Precompute for each interval the last non-overlapping interval
        prev = []
        for i in range(n):
            l = intervals[i][0]
            # Find rightmost j < i where intervals[j][1] < l
            j = bisect.bisect_left(ends, l) - 1
            prev.append(j)
        # DP: dp[i][k] = (score, path). 0-based i, k intervals used up to i
        # Initialize
        dp = [[(0, []) for _ in range(5)] for _ in range(n+1)]
        for i in range(1, n+1):
            for k in range(1, 5):
                # Not pick i-1th interval
                best = dp[i-1][k]
                # Pick i-1th interval, if possible
                j = prev[i-1]
                score, path = dp[j+1][k-1]
                cand = (score + intervals[i-1][2], path + [intervals[i-1][3]])
                # Compare by score, then lex
                if cand[0] > best[0] or (cand[0] == best[0] and cand[1] < best[1]):
                    best = cand
                dp[i][k] = best
        # Find best among dp[n][1], dp[n][2], dp[n][3], dp[n][4]
        answer = (0, [])
        for k in range(1, 5):
            if dp[n][k][0] > answer[0] or (dp[n][k][0] == answer[0] and dp[n][k][1] < answer[1]):
                answer = dp[n][k]
        return answer[1]
# @lc code=end