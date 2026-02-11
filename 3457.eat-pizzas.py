#
# @lc app=leetcode id=3457 lang=python3
#
# [3457] Eat Pizzas!
#

# @lc code=start
class Solution:
    def maxWeight(self, pizzas: List[int]) -> int:
        # Step 1: Sort the pizzas in ascending order
        pizzas.sort()
        n = len(pizzas)
        res = 0
        days = n // 4
        # Step 2: Partition pizzas into groups of 4 from largest to smallest
        for i in range(days):
            idx = n - 4 * i
            # For each group, select pizzas[idx-4] to pizzas[idx-1]
            # Step 3: Apply the day's rule for weight gain
            if i % 2 == 0:  # Odd day (1-indexed)
                res += pizzas[idx - 1]
            else:  # Even day
                res += pizzas[idx - 2]
        # Step 4: Verification step - in this context, sorting and grouping is justified because maximizing the highest values for Z and Y each day maximizes the gain, and all pizzas must be used exactly once in groups of four
        return res
# @lc code=end