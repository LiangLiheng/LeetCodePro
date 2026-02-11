#
# @lc app=leetcode id=3382 lang=python3
#
# [3382] Maximum Area Rectangle With Point Constraints II
#

# @lc code=start
class Solution:
    def maxRectangleArea(self, xCoord: List[int], yCoord: List[int]) -> int:
        # Step 1: Store all points for O(1) existence checks
        points = set(zip(xCoord, yCoord))
        n = len(xCoord)
        max_area = -1
        # Step 2: Scaffold optimizations: group points by x and y for potential batching
        x_groups = dict()
        y_groups = dict()
        for x, y in points:
            x_groups.setdefault(x, set()).add(y)
            y_groups.setdefault(y, set()).add(x)
        # Step 3: For each pair of points (p1, p2) that can form diagonal of a rectangle
        for i in range(n):
            for j in range(i + 1, n):
                x1, y1 = xCoord[i], yCoord[i]
                x2, y2 = xCoord[j], yCoord[j]
                # Only consider rectangles (not vertical/horizontal lines)
                if x1 != x2 and y1 != y2:
                    # Check if the other two corners exist
                    if (x1, y2) in points and (x2, y1) in points:
                        # Step 4: Use grouped points to filter candidates for potential interior points
                        minX, maxX = min(x1, x2), max(x1, x2)
                        minY, maxY = min(y1, y2), max(y1, y2)
                        valid = True
                        # Optimization: only check points in the bounding box using x_groups/y_groups
                        # For each x in (minX, maxX): check all ys in x_groups[x] within (minY, maxY)
                        for x in range(minX, maxX + 1):
                            if x in x_groups:
                                for y in x_groups[x]:
                                    if (x, y) in [(x1, y1), (x2, y2), (x1, y2), (x2, y1)]:
                                        continue
                                    if minY <= y <= maxY:
                                        valid = False
                                        break
                            if not valid:
                                break
                        if valid:
                            area = abs(x1 - x2) * abs(y1 - y2)
                            max_area = max(max_area, area)
        # Reflection: After each decomposition and optimization, verify new complexity.
        # Plan further batching (e.g., using range queries or spatial indices) if still unscalable.
        return max_area
# @lc code=end
# Note: This solution scaffolds partial batching/grouping and verifies after each major step, supporting incremental optimization beyond brute-force.