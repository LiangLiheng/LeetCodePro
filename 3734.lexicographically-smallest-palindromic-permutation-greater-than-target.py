#
# @lc app=leetcode id=3734 lang=python3
#
# [3734] Lexicographically Smallest Palindromic Permutation Greater Than Target
#

# @lc code=start
from collections import Counter

class Solution:
    def lexPalindromicPermutation(self, s: str, target: str) -> str:
        n = len(s)
        freq = Counter(s)
        odds = sum(1 for cnt in freq.values() if cnt % 2 == 1)
        if (n % 2 == 0 and odds > 0) or (n % 2 == 1 and odds != 1):
            return ""
        half = (n + 1) // 2
        m = n // 2
        for k in range(half, -1, -1):
            temp_freq = freq.copy()
            left = []
            possible = True
            for i in range(k):
                c = target[i]
                is_mid = (n % 2 == 1 and i == m)
                need = 1 if is_mid else 2
                if temp_freq[c] < need:
                    possible = False
                    break
                temp_freq[c] -= need
                left.append(c)
            if not possible:
                continue
            cand_left = left[:]
            if k == half:
                if all(cnt == 0 for cnt in temp_freq.values()):
                    pal = [""] * n
                    for i in range(half):
                        pal[i] = cand_left[i]
                    for i in range(m):
                        pal[n - 1 - i] = pal[i]
                    pal_str = ''.join(pal)
                    if pal_str > target:
                        return pal_str
                continue
            is_mid_k = (n % 2 == 1 and k == m)
            need_k = 1 if is_mid_k else 2
            chosen = None
            for o in range(ord(target[k]) + 1, ord('z') + 1):
                c = chr(o)
                if temp_freq[c] >= need_k:
                    chosen = c
                    break
            if chosen is None:
                continue
            temp_freq[chosen] -= need_k
            cand_left.append(chosen)
            fill_ok = True
            for pos in range(k + 1, half):
                is_mid_pos = (n % 2 == 1 and pos == m)
                need_pos = 1 if is_mid_pos else 2
                found = None
                for o in range(ord('a'), ord('z') + 1):
                    cc = chr(o)
                    if temp_freq[cc] >= need_pos:
                        found = cc
                        break
                if found is None:
                    fill_ok = False
                    break
                temp_freq[found] -= need_pos
                cand_left.append(found)
            if not fill_ok:
                continue
            pal = [""] * n
            for i in range(half):
                pal[i] = cand_left[i]
            for i in range(m):
                pal[n - 1 - i] = pal[i]
            return ''.join(pal)
        return ""
# @lc code=end