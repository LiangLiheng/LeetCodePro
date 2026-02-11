#
# @lc app=leetcode id=3455 lang=python3
#
# [3455] Shortest Matching Substring
#

# @lc code=start
from typing import List
import bisect

class Solution:
    def shortestMatchingSubstring(self, s: str, p: str) -> int:
        def find_all_starts(haystack: str, needle: str) -> List[int]:
            if not needle:
                return list(range(len(haystack) + 1))
            starts = []
            pos = 0
            while True:
                pos = haystack.find(needle, pos)
                if pos == -1:
                    break
                starts.append(pos)
                pos += 1
            return starts
        
        star1 = p.find('*')
        star2 = p.find('*', star1 + 1)
        A = p[:star1]
        B = p[star1 + 1:star2]
        C = p[star2 + 1:]
        lenA, lenB, lenC = len(A), len(B), len(C)
        n = len(s)
        posA = find_all_starts(s, A)
        posB = find_all_starts(s, B)
        posC = find_all_starts(s, C)
        
        ans = float('inf')
        for ib in posB:
            limit_ia = ib - lenA
            if limit_ia < 0:
                continue
            k = bisect.bisect_right(posA, limit_ia) - 1
            if k < 0:
                continue
            ia = posA[k]
            low_ic = ib + lenB
            if low_ic > n:
                continue
            m = bisect.bisect_left(posC, low_ic)
            if m >= len(posC):
                continue
            ic = posC[m]
            length = ic + lenC - ia
            if length < ans:
                ans = length
        return -1 if ans == float('inf') else ans
# @lc code=end