#
# @lc app=leetcode id=3779 lang=python3
#
# [3779] Minimum Number of Operations to Have Distinct Elements
#

# @lc code=start
class Solution:
    def minOperations(self, nums: List[int]) -> int:
        pos = {}
        for i, num in enumerate(nums):
            if num not in pos:
                pos[num] = []
            pos[num].append(i)
        m = -1
        for positions in pos.values():
            if len(positions) >= 2:
                m = max(m, positions[-2])
        if m == -1:
            return 0
        return (m + 3) // 3
# @lc code=end