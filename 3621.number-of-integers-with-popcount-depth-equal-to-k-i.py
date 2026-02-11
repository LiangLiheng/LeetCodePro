#
# @lc app=leetcode id=3621 lang=python3
#
# [3621] Number of Integers With Popcount-Depth Equal to K I
#

# @lc code=start
class Solution:
    def popcountDepth(self, n: int, k: int) -> int:
        if k == 0:
            return 1
        
        def get_depth(x: int) -> int:
            depth = 0
            while x > 1:
                x = bin(x).count('1')
                depth += 1
            return depth
        
        good_s = [s for s in range(1, 65) if get_depth(s) == k - 1]
        
        def count(target: int) -> int:
            bin_n_str = bin(n)[2:]
            L = len(bin_n_str)
            dp = [[[0 for _ in range(2)] for _ in range(target + 1)] for _ in range(L + 1)]
            
            for ti in range(2):
                for ones in range(target + 1):
                    dp[L][ones][ti] = 1 if ones == target else 0
            
            for pos in range(L - 1, -1, -1):
                for ones in range(target + 1):
                    for ti in range(2):
                        upper = 1 if ti == 0 else int(bin_n_str[pos])
                        val = 0
                        for d in range(upper + 1):
                            new_ti = 1 if ti == 1 and d == upper else 0
                            new_ones = ones + d
                            if new_ones > target:
                                continue
                            val += dp[pos + 1][new_ones][new_ti]
                        dp[pos][ones][ti] = val
            return dp[0][0][1]
        
        ans = sum(count(s) for s in good_s)
        if k == 1:
            ans -= 1
        return ans
# @lc code=end