#
# @lc app=leetcode id=3399 lang=python3
#
# [3399] Smallest Substring With Identical Characters II
#

# @lc code=start
class Solution:
    def minLength(self, s: str, numOps: int) -> int:
        n = len(s)
        def can_make(max_len):
            # Check for both possibilities: all '0' or all '1'
            for ch in '01':
                flips = 0
                left = 0
                for right in range(n):
                    if s[right] != ch:
                        flips += 1
                    if right - left + 1 > max_len:
                        if s[left] != ch:
                            flips -= 1
                        left += 1
                    if right - left + 1 == max_len and flips <= numOps:
                        return True
            return False

        low, high = 1, n
        res = n
        while low <= high:
            mid = (low + high) // 2
            if can_make(mid):
                res = mid
                high = mid - 1
            else:
                low = mid + 1
        # Verification step to ensure validity
        assert all(
            not (s[i:j].count('0') == j - i or s[i:j].count('1') == j - i)
            or (min(s[i:j].count('0'), s[i:j].count('1')) <= numOps)
            for i in range(n) for j in range(i + res + 1, n + 1)
        ), 'Verification failed: found a longer identical substring.'
        return res
# @lc code=end