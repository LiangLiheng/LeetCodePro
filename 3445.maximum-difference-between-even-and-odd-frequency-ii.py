#
# @lc app=leetcode id=3445 lang=python3
#
# [3445] Maximum Difference Between Even and Odd Frequency II
#

# @lc code=start
class Solution:
    def maxDifference(self, s: str, k: int) -> int:
        from collections import Counter
        n = len(s)
        max_diff = float('-inf')
        digits = ['0', '1', '2', '3', '4']
        for window_size in range(k, n+1):
            freq = Counter(s[:window_size])
            # Evaluate initial window
            for a in digits:
                if freq[a] % 2 == 1:
                    for b in digits:
                        if a != b and freq[b] > 0 and freq[b] % 2 == 0:
                            diff = freq[a] - freq[b]
                            max_diff = max(max_diff, diff)
            # Slide window
            for i in range(window_size, n):
                out_char = s[i-window_size]
                in_char = s[i]
                freq[out_char] -= 1
                freq[in_char] += 1
                for a in digits:
                    if freq[a] % 2 == 1:
                        for b in digits:
                            if a != b and freq[b] > 0 and freq[b] % 2 == 0:
                                diff = freq[a] - freq[b]
                                max_diff = max(max_diff, diff)
        return max_diff if max_diff != float('-inf') else -1
# @lc code=end