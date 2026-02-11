#
# @lc app=leetcode id=3414 lang=python3
#
# [3414] Maximum Score of Non-overlapping Intervals
#

# @lc code=start
from typing import List

class Solution:
    def maximumWeight(self, intervals: List[List[int]]) -> List[int]:
        n = len(intervals)
        if n == 0:
            return []
        events = [(inter[0], inter[1], inter[2], i) for i, inter in enumerate(intervals)]
        events.sort(key=lambda x: x[1])
        K = 4
        prefix_max = [[0] * (K + 1) for _ in range(n + 1)]
        prefix_paths = [[[] for _ in range(K + 1)] for _ in range(n + 1)]
        for i in range(n):
            start, end_time, weight, idx = events[i]
            # Compute dp for ending at i
            dp_1 = weight
            path_1 = [idx]
            # Binary search for largest m < i s.t. events[m][1] < start
            left, right = 0, i - 1
            m = -1
            while left <= right:
                mid = left + (right - left) // 2
                if events[mid][1] < start:
                    m = mid
                    left = mid + 1
                else:
                    right = mid - 1
            temp_dp = [0] * (K + 1)
            temp_paths = [[] for _ in range(K + 1)]
            temp_dp[1] = dp_1
            temp_paths[1] = path_1
            for j in range(2, K + 1):
                if m < 0:
                    break
                prev_max_s = prefix_max[j - 1][m + 1]
                if prev_max_s > 0:
                    new_score = prev_max_s + weight
                    temp_dp[j] = new_score
                    prev_path = prefix_paths[j - 1][m + 1][:]
                    new_path = sorted(prev_path + [idx])
                    temp_paths[j] = new_path
            # Update prefix for i+1: max(skip i, take i)
            for j in range(1, K + 1):
                score_skip = prefix_max[j][i]
                path_skip = prefix_paths[j][i]
                score_take = temp_dp[j]
                path_take = temp_paths[j]
                if score_take > score_skip:
                    prefix_max[j][i + 1] = score_take
                    prefix_paths[j][i + 1] = path_take
                elif score_take == score_skip:
                    prefix_max[j][i + 1] = score_skip
                    if path_take < path_skip:
                        prefix_paths[j][i + 1] = path_take
                    else:
                        prefix_paths[j][i + 1] = path_skip
                else:
                    prefix_max[j][i + 1] = score_skip
                    prefix_paths[j][i + 1] = path_skip
        # Global max score and lex min path
        max_score = 0
        best_list = []
        for j in range(1, K + 1):
            curr_score = prefix_max[j][n]
            curr_path = prefix_paths[j][n]
            if curr_score > max_score or (curr_score == max_score and (not best_list or curr_path < best_list)):
                max_score = curr_score
                best_list = curr_path
        return best_list

# @lc code=end