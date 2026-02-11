#
# @lc app=leetcode id=3504 lang=python3
#
# [3504] Longest Palindrome After Substring Concatenation II
#

# @lc code=start
class Solution:
    def longestPalindrome(self, s: str, t: str) -> int:
        def get_prefix(string: str, base: int, mod: int) -> tuple[list[int], list[int]]:
            n = len(string)
            prefix = [0] * (n + 1)
            power = [1] * (n + 1)
            for i in range(n):
                prefix[i + 1] = (prefix[i] * base + (ord(string[i]) - ord('a') + 1)) % mod
                power[i + 1] = (power[i] * base) % mod
            return prefix, power

        def get_hash(prefix: list[int], power: list[int], mod: int, left: int, right: int) -> int:
            res = (prefix[right] - prefix[left] * power[right - left] % mod + mod) % mod
            return res

        def compute_max_and_forward(string: str) -> tuple[int, list[int]]:
            n = len(string)
            if n == 0:
                return 0, []
            dp = [[False] * n for _ in range(n)]
            forward = [1] * n
            max_len = 1
            for i in range(n):
                dp[i][i] = True
            for i in range(n - 1):
                if string[i] == string[i + 1]:
                    dp[i][i + 1] = True
                    forward[i] = 2
                    max_len = 2
            for length in range(3, n + 1):
                for i in range(n - length + 1):
                    j = i + length - 1
                    if string[i] == string[j] and dp[i + 1][j - 1]:
                        dp[i][j] = True
                        forward[i] = max(forward[i], length)
                        max_len = max(max_len, length)
            return max_len, forward

        def compute_max_and_backward(string: str) -> tuple[int, list[int]]:
            n = len(string)
            if n == 0:
                return 0, []
            dp = [[False] * n for _ in range(n)]
            backward = [1] * n
            max_len = 1
            for i in range(n):
                dp[i][i] = True
            for i in range(n - 1):
                if string[i] == string[i + 1]:
                    dp[i][i + 1] = True
                    backward[i + 1] = 2
                    max_len = 2
            for length in range(3, n + 1):
                for i in range(n - length + 1):
                    j = i + length - 1
                    if string[i] == string[j] and dp[i + 1][j - 1]:
                        dp[i][j] = True
                        backward[j] = max(backward[j], length)
                        max_len = max(max_len, length)
            return max_len, backward

        ns = len(s)
        nt = len(t)
        max_s, forward_s = compute_max_and_forward(s)
        max_t, backward_t = compute_max_and_backward(t)
        ans = max(max_s, max_t)

        MOD1 = 10**9 + 7
        MOD2 = 10**9 + 9
        BASE1 = 31
        BASE2 = 37

        prefix_s1, power_s1 = get_prefix(s, BASE1, MOD1)
        prefix_s2, power_s2 = get_prefix(s, BASE2, MOD2)
        tr = t[::-1]
        prefix_tr1, power_tr1 = get_prefix(tr, BASE1, MOD1)
        prefix_tr2, power_tr2 = get_prefix(tr, BASE2, MOD2)

        def get_h_s(left: int, right: int, which: int) -> int:
            if which == 1:
                return get_hash(prefix_s1, power_s1, MOD1, left, right)
            return get_hash(prefix_s2, power_s2, MOD2, left, right)

        def get_h_tr(left: int, right: int, which: int) -> int:
            if which == 1:
                return get_hash(prefix_tr1, power_tr1, MOD1, left, right)
            return get_hash(prefix_tr2, power_tr2, MOD2, left, right)

        max_k = min(ns, nt)
        for k in range(1, max_k + 1):
            # Case 1: longer or equal in s (middle in s)
            set_tr_k = set()
            for j in range(nt - k + 1):
                h1 = get_h_tr(j, j + k, 1)
                h2 = get_h_tr(j, j + k, 2)
                set_tr_k.add((h1, h2))
            for start in range(ns - k + 1):
                hs1 = get_h_s(start, start + k, 1)
                hs2 = get_h_s(start, start + k, 2)
                if (hs1, hs2) in set_tr_k:
                    pos = start + k
                    m = forward_s[pos] if pos < ns else 0
                    ans = max(ans, 2 * k + m)

            # Case 2: longer or equal in t (middle in t)
            set_s_k = set()
            for b in range(ns - k + 1):
                h1 = get_h_s(b, b + k, 1)
                h2 = get_h_s(b, b + k, 2)
                set_s_k.add((h1, h2))
            for suf_start in range(nt - k + 1):
                j_start = nt - suf_start - k
                j_end = nt - suf_start
                htr1 = get_h_tr(j_start, j_end, 1)
                htr2 = get_h_tr(j_start, j_end, 2)
                if (htr1, htr2) in set_s_k:
                    p_end = suf_start - 1
                    p = backward_t[p_end] if p_end >= 0 else 0
                    ans = max(ans, 2 * k + p)
        return ans

# @lc code=end