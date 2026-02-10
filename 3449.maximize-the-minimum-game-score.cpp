#
# @lc app=leetcode id=3449 lang=cpp
#
# [3449] Maximize the Minimum Game Score
#
# @lc code=start
class Solution {
public:
    long long maxScore(vector<int>& points, int m) {
        int n = points.size();
        
        // Binary search on the answer
        long long left = 0, right = 1e15;
        
        auto canAchieve = [&](long long target) -> bool {
            if (target == 0) return true;
            
            long long totalVisits = 0;
            for (int i = 0; i < n; i++) {
                long long visits = (target + points[i] - 1) / points[i]; // ceil(target / points[i])
                totalVisits += visits;
                if (totalVisits > 1e15) return false; // Overflow check
            }
            
            long long moves = totalVisits + n - 2;
            return moves <= m;
        };
        
        long long ans = 0;
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            if (canAchieve(mid)) {
                ans = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return ans;
    }
};
# @lc code=end