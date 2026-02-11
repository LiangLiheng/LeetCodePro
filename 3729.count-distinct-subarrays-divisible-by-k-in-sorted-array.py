#
# @lc app=leetcode id=3729 lang=python3
#
# [3729] Count Distinct Subarrays Divisible by K in Sorted Array
#

# @lc code=start
from typing import List
import math

class Solution:
    def numGoodSubarrays(self, nums: List[int], k: int) -> int:
        if not nums:
            return 0
        # Compress into groups (val, freq)
        groups = []
        i = 0
        n = len(nums)
        while i < n:
            v = nums[i]
            freq = 0
            while i < n and nums[i] == v:
                freq += 1
                i += 1
            groups.append((v, freq))
        m = len(groups)
        prefix_mod = [0] * (m + 1)
        freq_left = {}
        ans = 0
        for i in range(m):
            v, f = groups[i]
            A = v % k
            full_mod = (f * A) % k
            next_prefix_mod = (prefix_mod[i] + full_mod) % k
            # Intra-group good subarrays
            g = math.gcd(A, k)
            period = k // g
            num_intra = f // period
            ans += num_intra
            # Spanning ending at this group i
            for ce in range(1, f + 1):
                ce_mod = (ce * A) % k
                right = (ce_mod + prefix_mod[i]) % k
                req = (k - right) % k
                ans += freq_left.get(req, 0)
            # Add left contributions for future ends
            for cs in range(1, f + 1):
                cs_mod = (cs * A) % k
                left_mod = (cs_mod - next_prefix_mod + k) % k
                freq_left[left_mod] = freq_left.get(left_mod, 0) + 1
            prefix_mod[i + 1] = next_prefix_mod
        return ans

# @lc code=end