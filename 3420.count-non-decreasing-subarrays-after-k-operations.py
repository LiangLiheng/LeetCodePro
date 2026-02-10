#
# @lc app=leetcode id=3420 lang=python3
#
# [3420] Count Non-Decreasing Subarrays After K Operations
#

# @lc code=start
from typing import List

class Solution:
    def countNonDecreasingSubarrays(self, nums: List[int], k: int) -> int:
        n = len(nums)
        if n == 0:
            return 0
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + nums[i]
        
        next_g = [n] * n
        stack = []
        for i in range(n - 1, -1, -1):
            while stack and nums[stack[-1]] <= nums[i]:
                stack.pop()
            if stack:
                next_g[i] = stack[-1]
            stack.append(i)
        
        cost_whole = [0] * n
        for i in range(n):
            t = next_g[i]
            if t > i + 1:
                nump = t - i - 1
                s = prefix[t] - prefix[i + 1]
                cost_whole[i] = nump * nums[i] - s
        
        LOG = 18
        parent = [[n] * n for _ in range(LOG)]
        cum_cost = [[0] * n for _ in range(LOG)]
        for i in range(n):
            parent[0][i] = next_g[i]
            cum_cost[0][i] = cost_whole[i]
        for lv in range(1, LOG):
            for i in range(n):
                mid = parent[lv - 1][i]
                if mid == n:
                    parent[lv][i] = n
                    cum_cost[lv][i] = cum_cost[lv - 1][i]
                else:
                    p2 = parent[lv - 1][mid]
                    parent[lv][i] = p2
                    cum_cost[lv][i] = cum_cost[lv - 1][i] + cum_cost[lv - 1][mid]
        
        total = 0
        def get_cost(start: int, endd: int) -> int:
            if endd <= start:
                return 0
            nump = endd - start
            s = prefix[endd + 1] - prefix[start + 1]
            return nump * nums[start] - s
        
        for l in range(n):
            spent = 0
            pos = l
            for bit in range(LOG - 1, -1, -1):
                if pos == n:
                    break
                addc = cum_cost[bit][pos]
                if spent + addc <= k:
                    anc = parent[bit][pos]
                    spent += addc
                    pos = anc
            if pos == n:
                max_rr = n - 1
            else:
                remain = k - spent
                t = next_g[pos]
                rr = n - 1 if t == n else t - 1
                lo = pos
                hi = rr
                res = pos - 1
                while lo <= hi:
                    m = lo + (hi - lo + 1) // 2
                    cc = get_cost(pos, m)
                    if cc <= remain:
                        res = m
                        lo = m + 1
                    else:
                        hi = m - 1
                max_rr = res
            total += max_rr - l + 1
        return total

# @lc code=end