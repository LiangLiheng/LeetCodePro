#
# @lc app=leetcode id=3605 lang=python3
#
# [3605] Minimum Stability Factor of Array
#

# @lc code=start
from typing import List
import math
from collections import defaultdict, deque

class Solution:
    def minStable(self, nums: List[int], maxC: int) -> int:
        n = len(nums)
        max_num = max(nums)
        # Step 1: Precompute possible divisors d >= 2 for all nums
        # To keep things tractable, only consider divisors up to a reasonable limit
        # or those present in the array, as opposed to every integer up to max_num.
        # For global correctness, collect divisors for all nums >= 2.
        divisor_count = defaultdict(int)
        for x in nums:
            upper = int(math.isqrt(x)) + 1
            for d in range(2, upper):
                if x % d == 0:
                    divisor_count[d] += 1
                    if d != x // d and x // d >= 2:
                        divisor_count[x // d] += 1
            if x >= 2:
                divisor_count[x] += 1
        divisors = [d for d in divisor_count]
        
        # Helper: For a given divisor d and length L, find all runs of length >= L
        def find_runs(d, L):
            runs = []
            start = None
            for i, x in enumerate(nums):
                if x % d == 0:
                    if start is None:
                        start = i
                else:
                    if start is not None and i - start >= L:
                        runs.append((start, i - 1))
                    start = None
            if start is not None and n - start >= L:
                runs.append((start, n - 1))
            return runs
        
        # For a given L, determine if we can disrupt all stable subarrays for all divisors
        def can_achieve(L):
            # For each divisor, collect all runs of length >= L
            all_runs = []
            for d in divisors:
                runs = find_runs(d, L)
                for run in runs:
                    all_runs.append(run)
            if not all_runs:
                return True # No runs, nothing to disrupt
            # Greedily select modification points to break all runs
            # Each modification breaks all runs covering that point
            # Use interval covering: pick the rightmost endpoint of current intervals
            all_runs.sort(key=lambda x: x[1])
            mods = 0
            covered_until = -1
            for left, right in all_runs:
                if left > covered_until:
                    # Place a modification at right
                    mods += 1
                    covered_until = right
                    if mods > maxC:
                        return False
            return mods <= maxC
        
        # Binary search for minimal L
        left, right = 1, n
        answer = n
        while left <= right:
            mid = (left + right) // 2
            if can_achieve(mid):
                answer = mid
                right = mid - 1
            else:
                left = mid + 1
        # Special case: can we remove all elements >=2 in <= maxC mods?
        count_ge2 = sum(1 for x in nums if x >= 2)
        if answer == 1 and count_ge2 <= maxC:
            return 0
        return answer
# @lc code=end