#
# @lc app=leetcode id=3677 lang=python3
#
# [3677] Count Binary Palindromic Numbers
#

# @lc code=start
class Solution:
    def countBinaryPalindromes(self, n: int) -> int:
        def is_palindrome(x):
            s = bin(x)[2:]
            return s == s[::-1]
        
        def create_palindrome(first_half, odd):
            res = first_half
            if odd:
                first_half //= 2
            while first_half:
                res = res * 2 + (first_half % 2)
                first_half //= 2
            return res
        
        result = 0
        max_len = n.bit_length()
        for length in range(1, max_len + 1):
            half_len = (length + 1) // 2
            start = 1 << (half_len - 1) if length > 1 else 0
            end = 1 << half_len
            for first_half in range(start, end):
                pal = create_palindrome(first_half, length % 2)
                if pal > n:
                    continue
                # Verification step: ensure pal is palindromic
                if is_palindrome(pal):
                    result += 1
        return result
# @lc code=end