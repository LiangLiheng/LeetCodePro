#
# @lc app=leetcode id=3464 lang=java
#
# [3464] Maximize the Distance Between Points on a Square
#
# @lc code=start
class Solution {
    public int maxDistance(int side, int[][] points, int k) {
        int n = points.length;
        int low = 0, high = 2 * side, ans = 0;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (canSelect(points, k, mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return ans;
    }
    private boolean canSelect(int[][] points, int k, int d) {
        int n = points.length;
        return backtrack(points, k, d, new boolean[n], 0, 0, new int[k]);
    }
    private boolean backtrack(int[][] points, int k, int d, boolean[] used, int start, int count, int[] chosen) {
        if (count == k) {
            // Explicitly verify all pairwise distances
            for (int i = 0; i < k; ++i) {
                for (int j = i + 1; j < k; ++j) {
                    int idx1 = chosen[i], idx2 = chosen[j];
                    int dist = Math.abs(points[idx1][0] - points[idx2][0]) + Math.abs(points[idx1][1] - points[idx2][1]);
                    if (dist < d) return false;
                }
            }
            return true;
        }
        int n = points.length;
        for (int i = start; i < n; ++i) {
            if (!used[i]) {
                boolean valid = true;
                for (int j = 0; j < count; ++j) {
                    int idx = chosen[j];
                    int dist = Math.abs(points[i][0] - points[idx][0]) + Math.abs(points[i][1] - points[idx][1]);
                    if (dist < d) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    used[i] = true;
                    chosen[count] = i;
                    if (backtrack(points, k, d, used, i + 1, count + 1, chosen)) return true;
                    used[i] = false;
                }
            }
        }
        return false;
    }
}
# @lc code=end