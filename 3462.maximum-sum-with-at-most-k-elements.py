#
# @lc app=leetcode id=3462 lang=python3
#
# [3462] Maximum Sum With at Most K Elements
#
# @lc code=start
class Solution:
    def maxSum(self, grid: List[List[int]], limits: List[int], k: int) -> int:
        n = len(grid)
        elements = []
        for i in range(n):
            for num in grid[i]:
                elements.append((num, i))
        elements.sort(reverse=True)
        row_picked = [0] * n
        total = 0
        cnt = 0
        for val, r in elements:
            if row_picked[r] < limits[r] and cnt < k:
                total += val
                row_picked[r] += 1
                cnt += 1
        return total
# @lc code=end