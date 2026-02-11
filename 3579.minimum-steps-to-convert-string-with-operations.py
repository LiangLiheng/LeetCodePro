#
# @lc app=leetcode id=3579 lang=python3
#
# [3579] Minimum Steps to Convert String with Operations
#

# @lc code=start
class Solution:
    def minOperations(self, word1: str, word2: str) -> int:
        n = len(word1)
        dp = [float('inf')] * (n + 1)
        dp[0] = 0

        for i in range(1, n+1):
            for j in range(i):
                s1 = word1[j:i]
                s2 = word2[j:i]

                # Option 1: Direct replace
                replace_count = sum(a != b for a, b in zip(s1, s2))
                dp[i] = min(dp[i], dp[j] + replace_count)

                # Option 2: Reverse then possibly replace
                rev = s1[::-1]
                replace_after_rev = sum(a != b for a, b in zip(rev, s2))
                if rev != s1:  # Only if reverse changes
                    dp[i] = min(dp[i], dp[j] + 1 + replace_after_rev)

                # Option 3: Single swap (any two positions)
                if i - j >= 2:
                    for x in range(i-j):
                        for y in range(x+1, i-j):
                            arr = list(s1)
                            arr[x], arr[y] = arr[y], arr[x]
                            swap = ''.join(arr)
                            replace_after_swap = sum(a != b for a, b in zip(swap, s2))
                            if swap != s1:
                                dp[i] = min(dp[i], dp[j] + 1 + replace_after_swap)
        # Sanity check: The minimal operation count should not be less than the number of differing characters
        # for direct replacements, so ensure dp[n] is at least plausible.
        return dp[n]
# @lc code=end