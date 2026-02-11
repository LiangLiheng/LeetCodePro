#
# @lc app=leetcode id=3621 lang=python3
#
# [3621] Number of Integers With Popcount-Depth Equal to K I
#

# @lc code=start
class Solution:
    def popcountDepth(self, n: int, k: int) -> int:
        from functools import lru_cache
        # Step 1: Precompute popcount-depth for possible s up to sufficient max_bits
        max_bits = n.bit_length() + 2  # Sufficiently covers all possible set bit counts
        depth = [-1] * (max_bits + 1)
        def get_depth(x):
            if x == 1:
                return 0
            if depth[x] != -1:
                return depth[x]
            d = 1 + get_depth(bin(x).count('1'))
            depth[x] = d
            return d
        for s in range(1, max_bits + 1):
            get_depth(s)
        # Step 2: Collect valid s for which popcount-depth(s) == k-1
        valid_s = []
        for s in range(1, max_bits + 1):
            if get_depth(s) == k - 1:
                valid_s.append(s)
        # Step 3: Count numbers <= n with exactly s set bits
        def count_numbers(n, s):
            bits = []
            tmp = n
            while tmp:
                bits.append(tmp & 1)
                tmp >>= 1
            bits = bits[::-1]
            m = len(bits)
            @lru_cache(None)
            def dp(pos, cnt, tight):
                if cnt < 0:
                    return 0
                if pos == m:
                    return 1 if cnt == 0 else 0
                res = 0
                up = bits[pos] if tight else 1
                for b in range(up + 1):
                    res += dp(pos + 1, cnt - b, tight and (b == up))
                return res
            return dp(0, s, True)
        # Step 5: Handle special case k == 0
        if k == 0:
            return 1 if n >= 1 else 0
        # Step 4: Sum results for all valid s and verify full coverage
        ans = 0
        for s in valid_s:
            ans += count_numbers(n, s)
        # Exclude x=0 (not in [1, n]) if needed
        if k == 1:
            ans -= 1
        # Step 6: Final verification is implicit in code structure and coverage
        return ans
# @lc code=end