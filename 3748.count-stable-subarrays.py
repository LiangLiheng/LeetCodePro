#
# @lc app=leetcode id=3748 lang=python3
#
# [3748] Count Stable Subarrays
#

# @lc code=start
class Solution:
    def countStableSubarrays(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        n = len(nums)
        # Preprocess: For each position, find the end of the maximal non-decreasing run starting at i
        run_end = [0]*n
        i = 0
        while i < n:
            j = i
            while j+1 < n and nums[j] <= nums[j+1]:
                j += 1
            for k in range(i, j+1):
                run_end[k] = j
            i = j+1
        ans = []
        for li, ri in queries:
            cnt = 0
            i = li
            while i <= ri:
                end = min(run_end[i], ri)
                L = end - i + 1
                cnt += L*(L+1)//2
                i = end + 1
            ans.append(cnt)
        return ans
# @lc code=end