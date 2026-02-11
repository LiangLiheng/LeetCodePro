#
# @lc app=leetcode id=3630 lang=python3
#
# [3630] Partition Array for Maximum XOR and AND
#

# @lc code=start
class Solution:
    def maximizeXorAndXor(self, nums: List[int]) -> int:
        n = len(nums)
        from functools import lru_cache
        
        @lru_cache(maxsize=None)
        def dfs(i, xa, ab, xc, has_b):
            if i == n:
                and_b = ab if has_b else 0
                return xa + and_b + xc
            # Option 1: assign nums[i] to A
            res1 = dfs(i+1, xa^nums[i], ab, xc, has_b)
            # Option 2: assign nums[i] to B
            if has_b:
                res2 = dfs(i+1, xa, ab & nums[i], xc, True)
            else:
                res2 = dfs(i+1, xa, nums[i], xc, True)
            # Option 3: assign nums[i] to C
            res3 = dfs(i+1, xa, ab, xc^nums[i], has_b)
            return max(res1, res2, res3)
        return dfs(0, 0, 0, 0, False)
# @lc code=end