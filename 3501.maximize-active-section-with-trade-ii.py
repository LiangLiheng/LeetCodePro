#
# @lc app=leetcode id=3501 lang=python3
#
# [3501] Maximize Active Section with Trade II
#

# @lc code=start
from typing import List

class Solution:
    def maxActiveSectionsAfterTrade(self, s: str, queries: List[List[int]]) -> List[int]:
        n = len(s)
        TOTAL = s.count('1')
        zeros = []
        i = 0
        while i < n:
            if s[i] == '1':
                i += 1
                continue
            start = i
            while i < n and s[i] == '0':
                i += 1
            zeros.append((start, i))
        Z = len(zeros)
        if Z < 2:
            return [TOTAL] * len(queries)
        adj_full = [zeros[p][1] - zeros[p][0] + zeros[p + 1][1] - zeros[p + 1][0] for p in range(Z - 1)]
        LOG = 18
        len_adj = Z - 1
        st = [[0] * len_adj for _ in range(LOG)]
        st[0] = adj_full[:]
        for j in range(1, LOG):
            for ii in range(len_adj - (1 << j) + 1):
                st[j][ii] = max(st[j - 1][ii], st[j - 1][ii + (1 << (j - 1))])
        def qmax(pleft: int, pright: int) -> int:
            if pleft > pright:
                return 0
            length = pright - pleft + 1
            k = 0
            while (1 << (k + 1)) <= length:
                k += 1
            return max(st[k][pleft], st[k][pright - (1 << k) + 1])
        ans = []
        for li, ri in queries:
            l = li
            r1 = ri + 1
            # find A: leftmost overlapping
            A = -1
            low = 0
            high = Z - 1
            while low <= high:
                mid = (low + high) // 2
                stt, enn = zeros[mid]
                if enn > l and stt <= ri:
                    A = mid
                    high = mid - 1
                elif stt > ri:
                    high = mid - 1
                else:
                    low = mid + 1
            if A == -1:
                ans.append(TOTAL)
                continue
            # find B: rightmost overlapping
            B = -1
            low = 0
            high = Z - 1
            while low <= high:
                mid = (low + high) // 2
                stt, enn = zeros[mid]
                if enn > l and stt <= ri:
                    B = mid
                    low = mid + 1
                elif stt > ri:
                    high = mid - 1
                else:
                    low = mid + 1
            if B < A + 1:
                ans.append(TOTAL)
                continue
            # clips
            stA, enA = zeros[A]
            clipA_ = min(enA, r1) - max(stA, l)
            stB, enB = zeros[B]
            clipB_ = min(enB, r1) - max(stB, l)
            maxs = 0
            # left pair p=A
            clip_next = clipB_ if A + 1 == B else (zeros[A + 1][1] - zeros[A + 1][0])
            maxs = max(maxs, clipA_ + clip_next)
            # right pair p=B-1
            clip_prev = clipA_ if B - 1 == A else (zeros[B - 1][1] - zeros[B - 1][0])
            maxs = max(maxs, clip_prev + clipB_)
            # middle pairs
            if A + 1 <= B - 2:
                mm = qmax(A + 1, B - 2)
                maxs = max(maxs, mm)
            ans.append(TOTAL + maxs)
        return ans

# @lc code=end