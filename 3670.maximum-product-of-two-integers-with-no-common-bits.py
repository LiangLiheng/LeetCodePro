#
# @lc app=leetcode id=3670 lang=python3
#
# [3670] Maximum Product of Two Integers With No Common Bits
#

# @lc code=start
class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        from collections import defaultdict
        bitmask_to_values = defaultdict(list)
        for num in nums:
            bm = num
            bitmask_to_values[bm].append(num)
        # For each bitmask, keep at most the two largest values
        for bm in bitmask_to_values:
            bitmask_to_values[bm].sort(reverse=True)
            if len(bitmask_to_values[bm]) > 2:
                bitmask_to_values[bm] = bitmask_to_values[bm][:2]
        unique_bitmasks = list(bitmask_to_values.keys())
        max_product = 0
        for i in range(len(unique_bitmasks)):
            bm1 = unique_bitmasks[i]
            v1s = bitmask_to_values[bm1]
            for j in range(i+1, len(unique_bitmasks)):
                bm2 = unique_bitmasks[j]
                if bm1 & bm2 == 0:
                    v2s = bitmask_to_values[bm2]
                    max_product = max(max_product, v1s[0] * v2s[0])
        return max_product
# @lc code=end