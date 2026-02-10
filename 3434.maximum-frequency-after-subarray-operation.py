#
# @lc app=leetcode id=3434 lang=python3
#
# [3434] Maximum Frequency After Subarray Operation
#

# @lc code=start
class Solution:
    def maxFrequency(self, nums: List[int], k: int) -> int:
        total_k = nums.count(k)
        max_freq = total_k
        for t in range(1, 51):
            max_ending_here = 0
            max_so_far = 0
            for num in nums:
                score = (num == t) - (num == k)
                max_ending_here = max(0, max_ending_here + score)
                max_so_far = max(max_so_far, max_ending_here)
            max_freq = max(max_freq, total_k + max_so_far)
        return max_freq
# @lc code=end