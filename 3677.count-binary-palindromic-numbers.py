#
# @lc app=leetcode id=3677 lang=python3
#
# [3677] Count Binary Palindromic Numbers
#

# @lc code=start
class Solution:
    def countBinaryPalindromes(self, n: int) -> int:
        if n == 0:
            return 1
        length = len(bin(n)[2:])
        count = 1  # for 0
        for l in range(1, length):
            count += 1 << ((l - 1) // 2)
        half_len = (length + 1) // 2
        low = 1 << (half_len - 1)
        high = (1 << half_len) - 1
        def gen_pal(left_val: int) -> int:
            full = 0
            p_l = 1 << (length - 1)
            p_r = 1
            h = half_len
            for i in range(h):
                bit = (left_val >> (h - 1 - i)) & 1
                full += bit * p_l
                if i < length - 1 - i:
                    full += bit * p_r
                p_l >>= 1
                p_r <<= 1
            return full
        l, r = low, high
        while l <= r:
            mid = l + (r - l) // 2
            if gen_pal(mid) <= n:
                l = mid + 1
            else:
                r = mid - 1
        add = r - low + 1 if r >= low else 0
        count += add
        return count

# @lc code=end