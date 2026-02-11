#
# @lc app=leetcode id=3510 lang=python3
#
# [3510] Minimum Pair Removal to Sort Array II
#

# @lc code=start
class Solution:
    def minimumPairRemoval(self, nums: List[int]) -> int:
        # Step 1: Initialize operation counter and copy the input array
        ops = 0
        arr = nums[:]
        while True:
            # Step 2: Check if arr is non-decreasing
            non_decreasing = True
            for i in range(1, len(arr)):
                if arr[i] < arr[i-1]:
                    non_decreasing = False
                    break
            if non_decreasing:
                return ops
            # Step 3: Find leftmost adjacent pair with minimal sum
            min_sum = float('inf')
            min_idx = -1
            for i in range(len(arr)-1):
                s = arr[i] + arr[i+1]
                if s < min_sum:
                    min_sum = s
                    min_idx = i
            # Step 4: Replace the pair at min_idx and min_idx+1 with their sum
            arr = arr[:min_idx] + [min_sum] + arr[min_idx+2:]
            ops += 1
            # Step 5: After each operation, verify progress and reassess approach for efficiency if the array is still large
# @lc code=end