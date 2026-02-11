#
# @lc app=leetcode id=3548 lang=python3
#
# [3548] Equal Sum Grid Partition II
#

# @lc code=start
class Solution:
    def canPartitionGrid(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        # Compute prefix sums for rows and columns
        total = 0
        row_sums = [0] * m
        col_sums = [0] * n
        for i in range(m):
            for j in range(n):
                total += grid[i][j]
                row_sums[i] += grid[i][j]
                col_sums[j] += grid[i][j]
        # Horizontal cuts
        prefix = 0
        for cut in range(1, m):
            prefix += row_sums[cut-1]
            part1 = prefix
            part2 = total - part1
            if part1 == part2:
                return True
            diff = abs(part1 - part2)
            # Try discounting a cell on the cut boundary row in either section
            for j in range(n):
                # Remove grid[cut-1][j] from part1
                if part1 - grid[cut-1][j] == part2:
                    return True
                # Remove grid[cut][j] from part2
                if part1 == part2 - grid[cut][j]:
                    return True
        # Vertical cuts
        prefix = 0
        for cut in range(1, n):
            prefix += col_sums[cut-1]
            part1 = prefix
            part2 = total - part1
            if part1 == part2:
                return True
            diff = abs(part1 - part2)
            # Try discounting a cell on the cut boundary column in either section
            for i in range(m):
                # Remove grid[i][cut-1] from part1
                if part1 - grid[i][cut-1] == part2:
                    return True
                # Remove grid[i][cut] from part2
                if part1 == part2 - grid[i][cut]:
                    return True
        return False
# @lc code=end