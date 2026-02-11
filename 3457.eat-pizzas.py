#
# @lc app=leetcode id=3457 lang=python3
#
# [3457] Eat Pizzas!
#

# @lc code=start
from typing import List

class Solution:
    def maxWeight(self, pizzas: List[int]) -> int:
        sp = sorted(pizzas, reverse=True)
        n = len(pizzas)
        days = n // 4
        num_odd = (days + 1) // 2
        num_even = days // 2
        ans = sum(sp[:num_odd])
        pos = num_odd
        for i in range(num_even):
            ans += sp[pos + 2 * i + 1]
        return ans

# @lc code=end