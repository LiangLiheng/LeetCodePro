#
# @lc app=leetcode id=3382 lang=java
#
# [3382] Maximum Area Rectangle With Point Constraints II
#

# @lc code=start
import java.util.*;
class Solution {
    public long maxRectangleArea(int[] xCoord, int[] yCoord) {
        int n = xCoord.length;
        Set<Long> pointSet = new HashSet<>();
        for (int i = 0; i < n; ++i) {
            long key = ((long) xCoord[i] << 32) | (long) yCoord[i];
            pointSet.add(key);
        }
        long maxArea = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int x1 = xCoord[i], y1 = yCoord[i];
                int x2 = xCoord[j], y2 = yCoord[j];
                if (x1 == x2 || y1 == y2) continue;
                // (x1, y2) and (x2, y1) should exist
                long p3 = ((long) x1 << 32) | (long) y2;
                long p4 = ((long) x2 << 32) | (long) y1;
                if (!pointSet.contains(p3) || !pointSet.contains(p4)) continue;
                // Find rectangle boundaries
                int minX = Math.min(x1, x2), maxX = Math.max(x1, x2);
                int minY = Math.min(y1, y2), maxY = Math.max(y1, y2);
                boolean valid = true;
                for (int k = 0; k < n; ++k) {
                    if (k == i || k == j) continue;
                    int x = xCoord[k], y = yCoord[k];
                    // Skip the four corners
                    if ((x == x1 && y == y2) || (x == x2 && y == y1)) continue;
                    if (x > minX && x < maxX && y > minY && y < maxY) {
                        valid = false;
                        break;
                    }
                    if ((x == minX || x == maxX) && (y > minY && y < maxY)) {
                        valid = false;
                        break;
                    }
                    if ((y == minY || y == maxY) && (x > minX && x < maxX)) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    long area = (long) (maxX - minX) * (maxY - minY);
                    if (area > maxArea) maxArea = area;
                }
            }
        }
        return maxArea;
    }
}
# @lc code=end