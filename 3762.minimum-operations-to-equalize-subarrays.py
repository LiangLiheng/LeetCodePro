#
# @lc app=leetcode id=3762 lang=python3
#
# [3762] Minimum Operations to Equalize Subarrays
#

# @lc code=start
from typing import List

class Solution:
    def minOperations(self, nums: List[int], k: int, queries: List[List[int]]) -> List[int]:
        n = len(nums)
        result = []
        for li, ri in queries:
            # Step 1: Extract subarray
            sub = nums[li:ri+1]
            # Step 2a: Calculate and store modulo k for all elements
            mod_vals = [x % k for x in sub]
            # Step 2b: Verify all modulos are identical
            if not all(m == mod_vals[0] for m in mod_vals):
                result.append(-1)
                continue
            # Step 6: Edge case, subarray of length 1
            if len(sub) == 1:
                result.append(0)
                continue
            # Step 3: Normalize all values
            norm = [(x - mod_vals[0]) // k for x in sub]
            # Step 4: Find median
            norm.sort()
            m = len(norm)
            median = norm[m // 2] if m % 2 == 1 else norm[(m-1)//2]
            # Step 5: Compute minimum number of operations
            min_ops = sum(abs(x - median) for x in norm)
            # Step 7: Verification (since only +/- k steps used, the process guarantees equalization)
            result.append(min_ops)
        # Step 8: Final reflection done by above structure
        return result
# @lc code=end