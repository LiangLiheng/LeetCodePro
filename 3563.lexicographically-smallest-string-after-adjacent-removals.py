#
# @lc app=leetcode id=3563 lang=python3
#
# [3563] Lexicographically Smallest String After Adjacent Removals
#

# @lc code=start
class Solution:
    def lexicographicallySmallestString(self, s: str) -> str:
        n = len(s)
        can_full = [[False] * (n + 1) for _ in range(n + 1)]
        for i in range(n + 1):
            can_full[i][i] = True
        
        def is_removable(a: str, b: str) -> bool:
            oa, ob = ord(a), ord(b)
            return abs(oa - ob) == 1 or {a, b} == {'a', 'z'}
        
        for leng in range(2, n + 1, 2):
            for i in range(n - leng + 1):
                j = i + leng
                for k in range(i + 1, j):
                    if is_removable(s[i], s[k]) and can_full[i + 1][k] and can_full[k + 1][j]:
                        can_full[i][j] = True
                        break
        
        min_str = [""] * (n + 1)
        for i in range(n - 1, -1, -1):
            candidates = [s[i] + min_str[i + 1]]
            for j in range(i + 1, n):
                if is_removable(s[i], s[j]) and can_full[i + 1][j]:
                    candidates.append(min_str[j + 1])
            min_str[i] = min(candidates)
        return min_str[0]

# @lc code=end