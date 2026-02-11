#
# @lc app=leetcode id=3513 lang=python3
#
# [3513] Number of Unique XOR Triplets I
#

# @lc code=start
from typing import List
class Solution:
    def uniqueXorTriplets(self, nums: List[int]) -> int:
        # Efficiently track unique XOR values for all possible triplets (i, j, k) with i <= j <= k
        n = len(nums)
        unique = set()
        # Use prefix XOR to compute subarray XORs in O(1)
        prefix = [0] * (n+1)
        for i in range(n):
            prefix[i+1] = prefix[i] ^ nums[i]
        # For every subarray nums[i:k+1], compute its XOR and add to the set
        for i in range(n):
            for k in range(i, n):
                xor_val = prefix[k+1] ^ prefix[i]
                unique.add(xor_val)
        return len(unique)
# @lc code=end