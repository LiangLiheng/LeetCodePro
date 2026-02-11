#
# @lc app=leetcode id=3458 lang=python3
#
# [3458] Select K Disjoint Special Substrings
#

# @lc code=start
class Solution:
    def maxSubstringLength(self, s: str, k: int) -> bool:
        if k == 0:
            return True
        from collections import defaultdict
        n = len(s)
        # Record first and last occurrence of each character
        first, last = {}, {}
        for i, c in enumerate(s):
            if c not in first:
                first[c] = i
            last[c] = i
        # Gather all valid candidate special substrings
        candidates = []
        i = 0
        while i < n:
            l = i
            r = last[s[i]]
            j = l
            while j <= r:
                r = max(r, last[s[j]])
                j += 1
            # Check if this substring is not the whole string
            if r - l + 1 < n:
                # Validate: all chars appear only inside [l, r]
                valid = True
                for idx in range(l, r + 1):
                    c = s[idx]
                    if first[c] < l or last[c] > r:
                        valid = False
                        break
                if valid:
                    candidates.append((l, r))
            i = r + 1
        # Select up to k disjoint substrings
        candidates.sort(key=lambda x: x[1])
        res = []
        prev_end = -1
        for l, r in candidates:
            if l > prev_end:
                res.append((l, r))
                prev_end = r
                if len(res) == k:
                    # Final verification to ensure all intervals are disjoint and valid
                    # (already ensured by construction and selection)
                    return True
        return False
# @lc code=end