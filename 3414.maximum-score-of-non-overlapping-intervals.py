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
        if n == 0:
            return []
        # (l, r, w, idx)
        ints = [(intervals[i][0], intervals[i][1], intervals[i][2], i) for i in range(n)]
        ints.sort(key=lambda x: x[1])  # sort by r
        ends = [inter[1] for inter in ints]
        
        INF = -1
        dp_score = [[INF] * 5 for _ in range(n)]
        dp_path = [[[] for _ in range(5)] for _ in range(n)]
        prefix_score = [[INF] * 5 for _ in range(n)]
        prefix_path = [[[] for _ in range(5)] for _ in range(n)]
        
        for i in range(n):
            l, r, w, orig_idx = ints[i]
            p = bisect.bisect_left(ends, l, 0, i) - 1
            
            for j in range(1, 5):
                if j == 1:
                    cand_score = w
                    cand_path = [orig_idx]
                else:
                    if p >= 0 and prefix_score[p][j - 1] >= 0:
                        prev_path = prefix_path[p][j - 1][:]
                        cand_path = sorted(prev_path + [orig_idx])
                        cand_score = prefix_score[p][j - 1] + w
                    else:
                        cand_score = INF
                        cand_path = []
                dp_score[i][j] = cand_score
                dp_path[i][j] = cand_path
            
            # update prefix
            for j in range(1, 5):
                prev_prefix_s = prefix_score[i - 1][j] if i > 0 else INF
                prev_prefix_p = prefix_path[i - 1][j][:] if i > 0 else []
                this_dp_s = dp_score[i][j]
                this_dp_p = dp_path[i][j]
                if this_dp_s > prev_prefix_s:
                    prefix_score[i][j] = this_dp_s
                    prefix_path[i][j] = this_dp_p[:]
                elif this_dp_s == prev_prefix_s and this_dp_s >= 0:
                    prefix_score[i][j] = this_dp_s  # Critical: propagate score on tie
                    if tuple(this_dp_p) < tuple(prev_prefix_p):
                        prefix_path[i][j] = this_dp_p[:]
                    else:
                        prefix_path[i][j] = prev_prefix_p[:]
                else:
                    prefix_score[i][j] = prev_prefix_s
                    prefix_path[i][j] = prev_prefix_p[:]
        
        # find best
        max_score = 0
        best_path = []
        for j in range(1, 5):
            s = prefix_score[n - 1][j]
            if s < 0:
                continue
            cand = prefix_path[n - 1][j][:]
            if s > max_score or (s == max_score and tuple(cand) < tuple(best_path)):
                max_score = s
                best_path = cand
        return best_path

# @lc code=end