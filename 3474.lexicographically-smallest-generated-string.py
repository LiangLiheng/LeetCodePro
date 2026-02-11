#
# @lc app=leetcode id=3474 lang=python3
#
# [3474] Lexicographically Smallest Generated String
#

# @lc code=start
class Solution:
    def generateString(self, str1: str, str2: str) -> str:
        n, m = len(str1), len(str2)
        total_len = n + m - 1
        word = [None] * total_len
        # Step 1: Place str2 at all 'T' positions and check for conflicts
        for i in range(n):
            if str1[i] == 'T':
                for j in range(m):
                    pos = i + j
                    if word[pos] is not None and word[pos] != str2[j]:
                        return ''
                    word[pos] = str2[j]
        # Step 2: Fill unset positions with 'a' for lex smallest
        for k in range(total_len):
            if word[k] is None:
                word[k] = 'a'
        word = ''.join(word)
        # Step 3: Re-validate all 'F' positions to ensure no forbidden substrings
        for i in range(n):
            if str1[i] == 'F':
                if word[i:i+m] == str2:
                    return ''
        return word
# @lc code=end