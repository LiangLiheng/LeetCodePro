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
        LOG = 18
        logg = [0] * (n + 1)
        for i in range(2, n + 1):
            logg[i] = logg[i // 2] + 1
        st = [[0] * n for _ in range(LOG)]
        for i in range(n):
            st[0][i] = nums[i]
        for j in range(1, LOG):
            for i in range(n - (1 << j) + 1):
                st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))])
        def query_max(L: int, R: int) -> int:
            if L >= R:
                return -1
            length = R - L
            lg = logg[length]
            return max(st[lg][L], st[lg][R - (1 << lg)])
        ng = [n] * n
        stack = []
        for i in range(n - 1, -1, -1):
            while stack and nums[stack[-1]] <= nums[i]:
                stack.pop()
            ng[i] = stack[-1] if stack else n
            stack.append(i)
        ans = 0
        l = 0
        cost = 0
        pmax = nums[0]
        for r in range(n):
            if r > 0:
                cost += max(0, pmax - nums[r])
                pmax = max(pmax, nums[r])
            while cost > k and l <= r:
                lo = l + 1
                hi = r + 1
                s = r + 1
                while lo <= hi:
                    mid = (lo + hi) // 2
                    if query_max(l + 1, mid) >= nums[l]:
                        s = mid
                        hi = mid - 1
                    else:
                        lo = mid + 1
                end = s - 1
                reduction = 0
                if end >= l + 1:
                    num_terms = end - l
                    sum_pm = 0
                    cur_pos = l + 1
                    while cur_pos <= end:
                        cur_maxx = nums[cur_pos]
                        nextp = ng[cur_pos]
                        segend = min(end, nextp - 1)
                        leng = segend - cur_pos + 1
                        sum_pm += cur_maxx * leng
                        cur_pos = nextp
                    reduction = nums[l] * num_terms - sum_pm
                cost -= reduction
                if nums[l] == pmax and l + 1 <= r:
                    pmax = query_max(l + 1, r + 1)
                l += 1
            ans += max(0, r - l + 1)
        return ans

# @lc code=end