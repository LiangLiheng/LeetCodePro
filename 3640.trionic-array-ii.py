#
# @lc app=leetcode id=3640 lang=python3
#
# [3640] Trionic Array II
#

# @lc code=start
from typing import List

class Solution:
    def maxSumTrionic(self, nums: List[int]) -> int:
        n = len(nums)
        INF = 10**20
        NEG_INF = -INF
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + nums[i]
        best_left_inc = [NEG_INF] * n
        best_right_add = [NEG_INF] * n
        # Process all maximal strict increasing runs for left inc and right add
        i = 0
        while i < n:
            s = i
            while i + 1 < n and nums[i + 1] > nums[i]:
                i += 1
            t = i
            if t - s >= 1:  # run length >=2
                # max_left_inc[p] for p = s+1 to t
                cur_min_pref = prefix[s]
                for p in range(s + 1, t + 1):
                    best_left_inc[p] = prefix[p + 1] - cur_min_pref
                    cur_min_pref = min(cur_min_pref, prefix[p])
                # best_right_add[q] for q = t-1 downto s
                cur_max_pref = prefix[t + 1]
                for q in range(t - 1, s - 1, -1):
                    best_right_add[q] = cur_max_pref - prefix[q + 1]
                    if q > s:
                        cur_max_pref = max(cur_max_pref, prefix[q + 1])
            i += 1
        # val[p] = best_left_inc[p] - prefix[p+1]
        val = [NEG_INF] * n
        for p in range(n):
            if best_left_inc[p] != NEG_INF:
                val[p] = best_left_inc[p] - prefix[p + 1]
        # Process all maximal strict decreasing runs for left_max[q]
        left_max = [NEG_INF] * n
        i = 0
        while i < n:
            u = i
            while i + 1 < n and nums[i + 1] < nums[i]:
                i += 1
            v = i
            if v - u >= 1:  # run length >=2
                cur_max_val = val[u]
                for q in range(u + 1, v + 1):
                    left_max[q] = prefix[q + 1] + cur_max_val
                    if q < v:
                        cur_max_val = max(cur_max_val, val[q])
            i += 1
        # Combine
        ans = NEG_INF
        for q in range(n - 1):
            if left_max[q] != NEG_INF and best_right_add[q] != NEG_INF:
                ans = max(ans, left_max[q] + best_right_add[q])
        return ans

# @lc code=end