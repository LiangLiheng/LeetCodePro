#
# @lc app=leetcode id=3575 lang=python3
#
# [3575] Maximum Good Subtree Score
#

# @lc code=start
from typing import List, Dict
class Solution:
    def goodSubtreeSum(self, vals: List[int], par: List[int]) -> int:
        MOD = 10**9 + 7
        n = len(vals)
        tree = [[] for _ in range(n)]
        for u, p in enumerate(par):
            if p != -1:
                tree[p].append(u)
        # Sanity check: Ensure tree structure matches input
        assert sum(len(children) for children in tree) == n - 1
        def get_digit_mask(val):
            mask = 0
            for d in str(val):
                bit = int(d)
                if (mask >> bit) & 1:
                    return None  # repeated digit in value itself
                mask |= (1 << bit)
            return mask
        maxScore = [0]*n
        def dfs(u):
            cur_mask = get_digit_mask(vals[u])
            dp: Dict[int,int] = {}
            if cur_mask is not None:
                dp[cur_mask] = vals[u]
            for v in tree[u]:
                child_dp = dfs(v)
                new_dp = dp.copy()
                for mask1, sum1 in dp.items():
                    for mask2, sum2 in child_dp.items():
                        if mask1 & mask2 == 0:
                            comb = mask1 | mask2
                            new_dp[comb] = max(new_dp.get(comb, 0), sum1 + sum2)
                for mask2, sum2 in child_dp.items():
                    new_dp[mask2] = max(new_dp.get(mask2, 0), sum2)
                # Prune redundant entries
                dp = new_dp
            maxScore[u] = max(dp.values()) if dp else 0
            return dp
        dfs(0)
        # Final verification: all nodes processed
        assert len(maxScore) == n
        return sum(maxScore) % MOD
# @lc code=end