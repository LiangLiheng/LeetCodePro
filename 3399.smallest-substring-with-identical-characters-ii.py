#
# @lc app=leetcode id=3399 lang=python3
#
# [3399] Smallest Substring With Identical Characters II
#
# @lc code=start
class Solution:
    def minLength(self, s: str, numOps: int) -> int:
        n = len(s)
        
        def can_achieve(k: int) -> bool:
            total_flips = 0
            i = 0
            while i < n:
                j = i
                while j < n and s[j] == s[i]:
                    j += 1
                length = j - i
                total_flips += length // (k + 1)
                if total_flips > numOps:
                    return False
                i = j
            return total_flips <= numOps
        
        left, right = 1, n
        while left < right:
            mid = (left + right) // 2
            if can_achieve(mid):
                right = mid
            else:
                left = mid + 1
        return left
# @lc code=end