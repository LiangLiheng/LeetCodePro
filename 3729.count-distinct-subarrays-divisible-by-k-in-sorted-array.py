#
# @lc app=leetcode id=3729 lang=python3
#
# [3729] Count Distinct Subarrays Divisible by K in Sorted Array
#

# @lc code=start
class Solution:
    def numGoodSubarrays(self, nums: List[int], k: int) -> int:
        n = len(nums)
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i+1] = prefix[i] + nums[i]
        seen = set()
        base = 911
        mod = 10**18 + 7
        for i in range(n):
            hash_val = 0
            for j in range(i, n):
                hash_val = (hash_val * base + nums[j]) % mod
                sub_sum = prefix[j+1] - prefix[i]
                if sub_sum % k == 0:
                    seen.add(hash_val)
        return len(seen)
# @lc code=end