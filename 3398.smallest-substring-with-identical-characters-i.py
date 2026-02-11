#
# @lc app=leetcode id=3398 lang=python3
#
# [3398] Smallest Substring With Identical Characters I
#

# @lc code=start
import math
class Solution:
    def minLength(self, s: str, numOps: int) -> int:
        n = len(s)
        def can_make(L):
            flips_needed = 0
            i = 0
            while i < n:
                j = i
                while j < n and s[j] == s[i]:
                    j += 1
                run_len = j - i
                if run_len > L:
                    flips_needed += math.ceil(run_len / L) - 1
                i = j
            return flips_needed <= numOps
        left, right = 1, n
        answer = n
        while left <= right:
            mid = (left + right) // 2
            if can_make(mid):
                answer = mid
                right = mid - 1
            else:
                left = mid + 1
        return answer
# @lc code=end