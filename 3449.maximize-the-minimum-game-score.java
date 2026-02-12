#
# @lc app=leetcode id=3449 lang=java
#
# [3449] Maximize the Minimum Game Score
#
# @lc code=start
class Solution {
    public long maxScore(int[] points, int m) {
        int n = points.length;
        long left = 0, right = (long) 1e16;
        while (left < right) {
            long mid = left + (right - left + 1) / 2;
            if (canAchieve(points, m, mid)) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        return left;
    }
    
    private boolean canAchieve(int[] points, int m, long minScore) {
        int n = points.length;
        int[] needed = new int[n];
        long totalVisits = 0;
        for (int i = 0; i < n; i++) {
            needed[i] = (int) Math.min((minScore + points[i] - 1) / points[i], m + 1);
            totalVisits += needed[i];
        }
        if (totalVisits > m) return false;
        // The minimal number of moves needed to visit each index k times is: (last index visited) + 2 * (sum of all additional visits)
        // Since you can only move left/right by 1, to visit each index needed[i] times, the minimal path is to go from left to right, visiting each as needed, with extra moves to return for extra visits.
        // In this greedy approach, it's enough to check if totalVisits <= m, since you can traverse left-to-right and revisit indices as needed (worst case).
        return true;
    }
}
# @lc code=end