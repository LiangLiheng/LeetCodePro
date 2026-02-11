#
# @lc app=leetcode id=3748 lang=python3
#
# [3748] Count Stable Subarrays
#

# @lc code=start
from typing import List

class Solution:
    def countStableSubarrays(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        n = len(nums)
        if n == 0:
            return []
        right = [0] * n
        right[n-1] = n - 1
        for i in range(n-2, -1, -1):
            if nums[i] <= nums[i + 1]:
                right[i] = right[i + 1]
            else:
                right[i] = i
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + right[i]
        left_reach = [0] * n
        ptr = 0
        for r in range(n):
            while ptr <= r and right[ptr] < r:
                ptr += 1
            left_reach[r] = ptr
        ans = []
        for li, ri in queries:
            l, r = li, ri
            length = r - l + 1
            total = length * (length + 1) // 2
            correction = 0
            if left_reach[r] > l:
                m = left_reach[r] - 1
                count_bad = m - l + 1
                sum_right_bad = prefix[m + 1] - prefix[l]
                correction = count_bad * r - sum_right_bad
            ans.append(total - correction)
        return ans
# @lc code=end