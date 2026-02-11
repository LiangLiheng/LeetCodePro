#
# @lc app=leetcode id=3441 lang=python3
#
# [3441] Minimum Cost Good Caption
#

# @lc code=start
class Solution:
    def minCostGoodCaption(self, caption: str) -> str:
        n = len(caption)
        import string
        dp = [(float('inf'), '') for _ in range(n+1)]
        dp[0] = (0, '')
        for i in range(3, n+1):
            for l in range(3, i+1):
                left = i - l
                if left < 0: break
                group = caption[left:i]
                for ch in string.ascii_lowercase:
                    cost = sum(1 for c in group if c != ch)
                    prev_cost, prev_str = dp[left]
                    total_cost = prev_cost + cost
                    candidate = prev_str + ch*l
                    if total_cost < dp[i][0]:
                        dp[i] = (total_cost, candidate)
                    elif total_cost == dp[i][0] and candidate < dp[i][1]:
                        dp[i] = (total_cost, candidate)
        if dp[n][0] == float('inf'):
            return ''
        return dp[n][1]
# @lc code=end