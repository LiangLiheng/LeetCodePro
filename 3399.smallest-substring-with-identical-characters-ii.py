#
# @lc app=leetcode id=3399 lang=python3
#
# [3399] Smallest Substring With Identical Characters II
#

# @lc code=start
class Solution:
    def minLength(self, s: str, numOps: int) -> int:
        n = len(s)
        def flips_needed(k: int) -> int:
            def simulate(start: int) -> int:
                cost = 0 if int(s[0]) == start else 1
                cur = start
                run = 1
                for i in range(1, n):
                    nxt = int(s[i])
                    if nxt == cur and run == k:
                        cost += 1
                        cur = 1 - cur
                        run = 1
                    elif nxt == cur:
                        run += 1
                    else:
                        cur = nxt
                        run = 1
                return cost
            return min(simulate(0), simulate(1))
        left = 1
        right = n
        while left < right:
            mid = left + (right - left) // 2
            if flips_needed(mid) <= numOps:
                right = mid
            else:
                left = mid + 1
        return left

# @lc code=end