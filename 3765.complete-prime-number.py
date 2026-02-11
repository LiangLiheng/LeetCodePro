#
# @lc app=leetcode id=3765 lang=python3
#
# [3765] Complete Prime Number
#

# @lc code=start
class Solution:
    def completePrime(self, num: int) -> bool:
        s = str(num)
        n = len(s)
        
        def is_prime(x: int) -> bool:
            if x <= 1:
                return False
            if x == 2 or x == 3:
                return True
            if x % 2 == 0 or x % 3 == 0:
                return False
            i = 5
            while i * i <= x:
                if x % i == 0 or x % (i + 2) == 0:
                    return False
                i += 6
            return True
        
        for i in range(1, n + 1):
            prefix = int(s[:i])
            suffix = int(s[n - i:])
            if not is_prime(prefix) or not is_prime(suffix):
                return False
        return True
# @lc code=end