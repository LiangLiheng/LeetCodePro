#
# @lc app=leetcode id=3739 lang=python3
#
# [3739] Count Subarrays With Majority Element II
#

# @lc code=start
class Solution:
    def countMajoritySubarrays(self, nums: List[int], target: int) -> int:
        n = len(nums)
        offset = n + 1
        MAXV = 2 * n + 5
        ft = [0] * (MAXV + 1)
        def update(idx):
            while idx <= MAXV:
                ft[idx] += 1
                idx += idx & -idx
        def query(idx):
            res = 0
            while idx > 0:
                res += ft[idx]
                idx -= idx & -idx
            return res
        ans = 0
        prefix = 0
        update(offset + prefix)
        for num in nums:
            prefix += 1 if num == target else -1
            ans += query(offset + prefix - 1)
            update(offset + prefix)
        return ans

# @lc code=end