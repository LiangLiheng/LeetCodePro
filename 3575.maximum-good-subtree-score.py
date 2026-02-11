#
# @lc app=leetcode id=3575 lang=python3
#
# [3575] Maximum Good Subtree Score
#

# @lc code=start
from typing import List

class Solution:
    def goodSubtreeSum(self, vals: List[int], par: List[int]) -> int:
        MOD = 10**9 + 7
        n = len(vals)
        children = [[] for _ in range(n)]
        for i in range(1, n):
            children[par[i]].append(i)
        N = 1 << 10
        ans = [0]

        def get_mask(val: int) -> int | None:
            digits = set()
            mask = 0
            for c in str(val):
                d = int(c)
                if d in digits:
                    return None
                digits.add(d)
                mask |= (1 << d)
            return mask

        def dfs(u: int) -> List[int]:
            own_mask = get_mask(vals[u])
            dp = [-1] * N
            dp[0] = 0
            for v in children[u]:
                child_dp = dfs(v)
                valid_curr = [m for m in range(N) if dp[m] != -1]
                valid_ch = [m for m in range(N) if child_dp[m] != -1]
                new_dp = [-1] * N
                for m1 in valid_curr:
                    for m2 in valid_ch:
                        if (m1 & m2) == 0:
                            nm = m1 | m2
                            ns = dp[m1] + child_dp[m2]
                            if new_dp[nm] == -1 or ns > new_dp[nm]:
                                new_dp[nm] = ns
                dp = new_dp
            subtree_dp = dp[:]
            if own_mask is not None:
                valid_ch = [m for m in range(N) if dp[m] != -1]
                for m in valid_ch:
                    if (own_mask & m) == 0:
                        nm = own_mask | m
                        ns = vals[u] + dp[m]
                        if subtree_dp[nm] == -1 or ns > subtree_dp[nm]:
                            subtree_dp[nm] = ns
            max_s = 0
            for val in subtree_dp:
                if val != -1 and val > max_s:
                    max_s = val
            ans[0] = (ans[0] + max_s) % MOD
            return subtree_dp

        dfs(0)
        return ans[0]

# @lc code=end