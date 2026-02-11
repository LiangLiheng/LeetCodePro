#
# @lc app=leetcode id=3739 lang=python3
#
# [3739] Count Subarrays With Majority Element II
#

# @lc code=start
from typing import List
from collections import defaultdict
import bisect

class Solution:
    def countMajoritySubarrays(self, nums: List[int], target: int) -> int:
        # Transform nums into +1 (target) and -1 (not target)
        arr = [1 if num == target else -1 for num in nums]
        prefix = [0]
        for v in arr:
            prefix.append(prefix[-1] + v)
        # We want to count number of pairs (i, j) with i < j where prefix[j] > prefix[i]
        # Use a sorted list to maintain prefix sums
        from bisect import bisect_left, insort
        res = 0
        sl = [0]
        for i in range(1, len(prefix)):
            # Count number of prefix sums less than prefix[i]
            pos = bisect_left(sl, prefix[i])
            res += pos
            insort(sl, prefix[i])
        return res
# @lc code=end