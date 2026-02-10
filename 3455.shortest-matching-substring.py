#
# @lc app=leetcode id=3455 lang=python3
#
# [3455] Shortest Matching Substring
#

# @lc code=start
class Solution:
    def shortestMatchingSubstring(self, s: str, p: str) -> int:
        import bisect

        def compute_pi(pattern: str) -> list[int]:
            m = len(pattern)
            pi = [0] * m
            j = 0
            for i in range(1, m):
                while j > 0 and pattern[i] != pattern[j]:
                    j = pi[j - 1]
                if pattern[i] == pattern[j]:
                    j += 1
                pi[i] = j
            return pi

        def get_starts(hay: str, needle: str) -> list[int]:
            n = len(hay)
            if not needle:
                return list(range(n + 1))
            m = len(needle)
            if m > n:
                return []
            pi = compute_pi(needle)
            starts = []
            j = 0
            for i in range(n):
                while j > 0 and hay[i] != needle[j]:
                    j = pi[j - 1]
                if hay[i] == needle[j]:
                    j += 1
                if j == m:
                    starts.append(i - m + 1)
                    j = pi[j - 1]
            return starts

        def get_ends(hay: str, needle: str) -> list[int]:
            n = len(hay)
            if not needle:
                return list(range(n + 1))
            starts = get_starts(hay, needle)
            return [st + len(needle) for st in starts]

        stars = [i for i, c in enumerate(p) if c == '*']
        pos1, pos2 = stars
        A = p[:pos1]
        B = p[pos1 + 1:pos2]
        C = p[pos2 + 1:]
        lenA, lenB, lenC = len(A), len(B), len(C)
        n = len(s)
        list_l = get_starts(s, A)
        list_j = get_starts(s, B)
        list_r = get_ends(s, C)
        min_len = float('inf')
        for j in list_j:
            upper_l = j - lenA
            if upper_l < 0:
                continue
            idx = bisect.bisect_right(list_l, upper_l) - 1
            if idx < 0:
                continue
            l_pos = list_l[idx]
            low_r = j + lenB + lenC
            if low_r > n:
                continue
            idxr = bisect.bisect_left(list_r, low_r)
            if idxr >= len(list_r):
                continue
            r_pos = list_r[idxr]
            cand = r_pos - l_pos
            if cand < min_len:
                min_len = cand
        return min_len if min_len < float('inf') else -1

# @lc code=end