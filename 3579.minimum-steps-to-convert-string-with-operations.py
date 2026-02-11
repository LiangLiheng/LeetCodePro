#
# @lc app=leetcode id=3579 lang=python3
#
# [3579] Minimum Steps to Convert String with Operations
#

# @lc code=start
class Solution:
    def minOperations(self, word1: str, word2: str) -> int:
        n = len(word1)
        INF = 10**9 + 7
        dp = [INF] * (n + 1)
        dp[0] = 0
        def get_cost(l: int, r: int) -> int:
            k = r - l + 1
            # no reverse
            count = [[0] * 26 for _ in range(26)]
            mism = 0
            for i in range(l, r + 1):
                x = ord(word1[i]) - ord('a')
                y = ord(word2[i]) - ord('a')
                if x != y:
                    count[x][y] += 1
                    mism += 1
            max_pairs = 0
            for x in range(26):
                for y in range(x + 1, 26):
                    max_pairs += min(count[x][y], count[y][x])
            cost1 = mism - max_pairs
            # reverse
            count = [[0] * 26 for _ in range(26)]
            mism = 0
            for i in range(k):
                rev_pos = l + k - 1 - i
                x = ord(word1[rev_pos]) - ord('a')
                y = ord(word2[l + i]) - ord('a')
                if x != y:
                    count[x][y] += 1
                    mism += 1
            max_pairs = 0
            for x in range(26):
                for y in range(x + 1, 26):
                    max_pairs += min(count[x][y], count[y][x])
            cost2 = mism - max_pairs + 1
            return min(cost1, cost2)
        for i in range(1, n + 1):
            for j in range(i):
                c = get_cost(j, i - 1)
                if dp[j] < INF:
                    dp[i] = min(dp[i], dp[j] + c)
        return dp[n]
# @lc code=end