#
# @lc app=leetcode id=3598 lang=python3
#
# [3598] Longest Common Prefix Between Adjacent Strings After Removals
#

# @lc code=start
class Solution:
    def longestCommonPrefix(self, words: List[str]) -> List[int]:
        def common_prefix(a, b):
            l = min(len(a), len(b))
            for i in range(l):
                if a[i] != b[i]:
                    return i
            return l
        n = len(words)
        if n == 1:
            return [0]
        # Precompute all adjacent prefixes
        prefix = [common_prefix(words[i], words[i+1]) for i in range(n-1)]
        answer = [0]*n
        for i in range(n):
            new_prefixes = []
            # Add unchanged prefixes before the affected area
            if i > 1:
                new_prefixes.extend(prefix[:i-1])
            # Add new/updated prefix between words[i-1] and words[i+1] if both exist
            if 0 < i < n-1:
                new_prefixes.append(common_prefix(words[i-1], words[i+1]))
            # Add unchanged prefixes after the affected area
            if i < n-2:
                new_prefixes.extend(prefix[i+1:])
            answer[i] = max(new_prefixes) if new_prefixes else 0
        return answer
# @lc code=end