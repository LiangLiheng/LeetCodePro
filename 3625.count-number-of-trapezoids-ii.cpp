#
# @lc app=leetcode id=3625 lang=cpp
#
# [3625] Count Number of Trapezoids II
#
# @lc code=start
class Solution {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        int n = points.size();
        int count = 0;
        
        // Try all combinations of 4 points
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    for (int l = k + 1; l < n; l++) {
                        if (isTrapezoid(points[i], points[j], points[k], points[l])) {
                            count++;
                        }
                    }
                }
            }
        }
        
        return count;
    }
    
private:
    bool isTrapezoid(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        // Check if any three points are collinear (would make invalid quadrilateral)
        if (areCollinear(p1, p2, p3) || areCollinear(p1, p2, p4) || 
            areCollinear(p1, p3, p4) || areCollinear(p2, p3, p4)) {
            return false;
        }
        
        // Check if at least one pair of opposite sides is parallel
        // There are 3 ways to pair 4 points into opposite sides
        bool pair1 = isParallel(p1, p2, p3, p4);  // (p1,p2) with (p3,p4)
        bool pair2 = isParallel(p1, p3, p2, p4);  // (p1,p3) with (p2,p4)
        bool pair3 = isParallel(p1, p4, p2, p3);  // (p1,p4) with (p2,p3)
        
        return pair1 || pair2 || pair3;
    }
    
    bool areCollinear(vector<int>& p1, vector<int>& p2, vector<int>& p3) {
        // Three points are collinear if cross product is zero
        long long dx1 = p2[0] - p1[0];
        long long dy1 = p2[1] - p1[1];
        long long dx2 = p3[0] - p1[0];
        long long dy2 = p3[1] - p1[1];
        
        return dx1 * dy2 == dx2 * dy1;
    }
    
    bool isParallel(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        // Two lines are parallel if they have the same slope
        // Using cross product to avoid division: (y2-y1)/(x2-x1) == (y4-y3)/(x4-x3)
        // Equivalent to: (y2-y1)*(x4-x3) == (y4-y3)*(x2-x1)
        long long dx1 = p2[0] - p1[0];
        long long dy1 = p2[1] - p1[1];
        long long dx2 = p4[0] - p3[0];
        long long dy2 = p4[1] - p3[1];
        
        return dy1 * dx2 == dy2 * dx1;
    }
};
# @lc code=end