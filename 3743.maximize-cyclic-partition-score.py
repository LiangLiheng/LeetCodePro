#
# @lc app=leetcode id=3743 lang=python3
#
# [3743] Maximize Cyclic Partition Score
#

# @lc code=start
class Solution:
    def maximumScore(self, nums: List[int], k: int) -> int:
        n = len(nums)
        if n == 0:
            return 0
        sorted_nums = sorted(nums)
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + sorted_nums[i]
        ans = 0
        max_m = min(k, n)
        for m in range(1, max_m + 1):
            sum_top = prefix[n] - prefix[n - m]
            sum_bot = prefix[m]
            ans = max(ans, sum_top - sum_bot)
        return ans

# @lc code=end