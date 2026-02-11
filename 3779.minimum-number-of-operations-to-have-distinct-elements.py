#
# @lc app=leetcode id=3779 lang=python3
#
# [3779] Minimum Number of Operations to Have Distinct Elements
#

# @lc code=start
class Solution:
    def minOperations(self, nums: List[int]) -> int:
        n = len(nums)
        if len(set(nums)) == n:
            return 0
        ops = 0
        start = 0
        while start < n:
            # Simulate removing first three elements
            start += 3
            # If array is empty after removal
            if start >= n:
                ops += 1
                break
            rest = nums[start:]
            # Efficiently check for duplicates only in the remaining elements
            if len(set(rest)) == len(rest):
                ops += 1
                break
            ops += 1
        # Final verification for correctness
        return ops
# @lc code=end