#
# @lc app=leetcode id=3509 lang=python3
#
# [3509] Maximum Product of Subsequences With an Alternating Sum Equal to K
#

# @lc code=start
from typing import List
class Solution:
    def maxProduct(self, nums: List[int], k: int, limit: int) -> int:
        from functools import lru_cache
        n = len(nums)
        res = -1

        @lru_cache(maxsize=None)
        def dp(i, alt_sum, parity, prod, used):
            nonlocal res
            if i == n:
                if used > 0 and alt_sum == k and prod <= limit:
                    res = max(res, prod)
                return
            # Skip current element
            dp(i+1, alt_sum, parity, prod, used)
            # Include current element, update parity and alternating sum
            new_prod = prod * nums[i]
            if new_prod <= limit:
                if parity == 0:
                    next_alt_sum = alt_sum + nums[i]
                else:
                    next_alt_sum = alt_sum - nums[i]
                dp(i+1, next_alt_sum, 1-parity, new_prod, used+1)
        dp(0, 0, 0, 1, 0)
        return res
# @lc code=end