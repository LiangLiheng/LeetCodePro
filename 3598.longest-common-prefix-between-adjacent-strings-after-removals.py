#
# @lc app=leetcode id=3598 lang=python3
#
# [3598] Longest Common Prefix Between Adjacent Strings After Removals
#

# @lc code=start
from typing import List

class Solution:
    def longestCommonPrefix(self, words: List[str]) -> List[int]:
        def lcp(a: str, b: str) -> int:
            res = 0
            l = min(len(a), len(b))
            while res < l and a[res] == b[res]:
                res += 1
            return res
        n = len(words)
        answer = [0] * n
        if n <= 1:
            return answer
        prefix_len = [0] * (n - 1)
        for j in range(n - 1):
            prefix_len[j] = lcp(words[j], words[j + 1])
        pre_max = [0] * n
        for j in range(n - 1):
            pre_max[j + 1] = max(pre_max[j], prefix_len[j])
        suf_max = [0] * n
        suf_max[n - 1] = 0
        for j in range(n - 2, -1, -1):
            suf_max[j] = max(suf_max[j + 1], prefix_len[j])
        for i in range(n):
            if i == 0:
                kept_max = 0 if n < 2 else suf_max[1]
            elif i == n - 1:
                kept_max = 0 if n < 2 else pre_max[n - 2]
            else:
                kept_max = max(pre_max[i - 1], suf_max[i + 1])
            new_lcp_val = 0
            if 1 <= i <= n - 2:
                new_lcp_val = lcp(words[i - 1], words[i + 1])
            answer[i] = max(kept_max, new_lcp_val)
        return answer
# @lc code=end