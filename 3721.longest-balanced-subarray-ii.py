#
# @lc app=leetcode id=3721 lang=python3
#
# [3721] Longest Balanced Subarray II
#
# @lc code=start
class Solution:
    def longestBalanced(self, nums: List[int]) -> int:
        # Step 1: Initialize variables to track result, window, and distinct counts
        n = len(nums)
        max_len = 0
        left = 0
        even_count = {}
        odd_count = {}
        # Step 2: Expand the window to the right
        for right in range(n):
            num = nums[right]
            if num % 2 == 0:
                even_count[num] = even_count.get(num, 0) + 1
            else:
                odd_count[num] = odd_count.get(num, 0) + 1
            # Step 3: While the window is valid, try to maximize it
            while left <= right:
                if len(even_count) == len(odd_count):
                    max_len = max(max_len, right - left + 1)
                    break  # this is the largest window for this right, go to next right
                # Otherwise, shrink window from left
                lnum = nums[left]
                if lnum % 2 == 0:
                    even_count[lnum] -= 1
                    if even_count[lnum] == 0:
                        del even_count[lnum]
                else:
                    odd_count[lnum] -= 1
                    if odd_count[lnum] == 0:
                        del odd_count[lnum]
                left += 1
        return max_len
# @lc code=end