#
# @lc app=leetcode id=3413 lang=python3
#
# [3413] Maximum Coins From K Consecutive Bags
#

# @lc code=start
from typing import List
import bisect

class Solution:
    def maximumCoins(self, coins: List[List[int]], k: int) -> int:
        if k == 0:
            return 0
        events = []
        for li, ri, ci in coins:
            events.append((li, ci))
            events.append((ri + 1, -ci))
        events.sort(key=lambda e: (e[0], -e[1]))
        pos_set = set(e[0] for e in events)
        pos_list = sorted(pos_set)
        m = len(pos_list)
        if m == 0:
            return 0
        prefix_s = [0] * (m + 1)
        density_after = [0] * m
        jj = 0  # renamed to avoid conflict with loop var
        cur_density = 0
        cur_s = 0
        last_pos = 0
        for i in range(m):
            p = pos_list[i]
            if p > last_pos + 1:
                num_bags = p - last_pos - 1
                cur_s += cur_density * num_bags
            while jj < len(events) and events[jj][0] == p:
                cur_density += events[jj][1]
                jj += 1
            cur_s += cur_density
            prefix_s[i + 1] = cur_s
            density_after[i] = cur_density
            last_pos = p
        def get_S(x: int) -> int:
            if x < 1:
                return 0
            idx = bisect.bisect_right(pos_list, x) - 1
            if idx < 0:
                return 0
            base = prefix_s[idx + 1]
            rem = x - pos_list[idx]
            return base + density_after[idx] * rem
        ans = 0
        for p in pos_list:
            j = p - 1
            curr = get_S(j) - get_S(j - k)
            if curr > ans:
                ans = curr
            j = p + k - 1
            curr = get_S(j) - get_S(j - k)
            if curr > ans:
                ans = curr
        return ans

# @lc code=end