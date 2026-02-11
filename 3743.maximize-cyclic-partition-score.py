#
# @lc app=leetcode id=3743 lang=python3
#
# [3743] Maximize Cyclic Partition Score
#

# @lc code=start
from typing import List

class Solution:
    def maximumScore(self, nums: List[int], k: int) -> int:
        n = len(nums)
        nums2 = nums + nums
        max_score = 0
        for start in range(n):
            window = nums2[start:start+n]
            # Precompute min and max for all subarrays
            min_in = [[0]*n for _ in range(n)]
            max_in = [[0]*n for _ in range(n)]
            for i in range(n):
                min_in[i][i] = window[i]
                max_in[i][i] = window[i]
                for j in range(i+1, n):
                    min_in[i][j] = min(min_in[i][j-1], window[j])
                    max_in[i][j] = max(max_in[i][j-1], window[j])
            # DP: dp[i][j] = max sum of ranges for first i elements with j partitions
            dp = [[float('-inf')] * (k+1) for _ in range(n+1)]
            dp[0][0] = 0  # 0 elements, 0 partitions, score 0
            for i in range(1, n+1):
                for part in range(1, min(k, i)+1):
                    for cut in range(part-1, i):
                        prev = dp[cut][part-1]
                        if prev == float('-inf'):
                            continue
                        rng = max_in[cut][i-1] - min_in[cut][i-1]
                        dp[i][part] = max(dp[i][part], prev + rng)
            # After DP, check for maximum score among all partition counts
            local_max = max(dp[n][1:k+1])
            max_score = max(max_score, local_max)
            # Optional: assert to verify DP correctness
            assert all(x == float('-inf') or x >= 0 for x in dp[n][1:k+1])
        return max_score
# @lc code=end