#
# @lc app=leetcode id=3458 lang=python3
#
# [3458] Select K Disjoint Special Substrings
#

# @lc code=start
from typing import List
import bisect

class Solution:
    def maxSubstringLength(self, s: str, k: int) -> bool:
        n = len(s)
        if k == 0:
            return True
        first_pos = [-1] * 26
        last_pos = [-1] * 26
        pos_lists = [[] for _ in range(26)]
        for i in range(n):
            c = ord(s[i]) - ord('a')
            pos_lists[c].append(i)
            if first_pos[c] == -1:
                first_pos[c] = i
            last_pos[c] = i
        starts = [first_pos[c] for c in range(26) if first_pos[c] != -1]
        ends_ = [last_pos[c] for c in range(26) if last_pos[c] != -1]
        special_intervals = []
        for l in starts:
            for r in ends_:
                if l > r:
                    continue
                if l == 0 and r == n - 1:
                    continue
                is_special = True
                for cc in range(26):
                    if not pos_lists[cc]:
                        continue
                    plist = pos_lists[cc]
                    idx = bisect.bisect_left(plist, l)
                    if idx < len(plist) and plist[idx] <= r:
                        if first_pos[cc] < l or last_pos[cc] > r:
                            is_special = False
                            break
                if is_special:
                    special_intervals.append((l, r))
        special_intervals.sort(key=lambda x: x[1])
        count = 0
        prev_end = -1
        for l, r in special_intervals:
            if l > prev_end:
                count += 1
                prev_end = r
                if count >= k:
                    return True
        return count >= k
# @lc code=end