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
        vector<vector<int>*> pts = {&p1, &p2, &p3, &p4};
        
        vector<vector<int>> orderings = {
            {0,1,2,3}, {0,1,3,2}, {0,2,1,3}, {0,2,3,1}, {0,3,1,2}, {0,3,2,1}
        };
        
        for (auto& ord : orderings) {
            if (isValidTrapezoid(pts[ord[0]], pts[ord[1]], pts[ord[2]], pts[ord[3]])) {
                return true;
            }
        }
        
        return false;
    }
    
    bool isValidTrapezoid(vector<int>* a, vector<int>* b, vector<int>* c, vector<int>* d) {
        // First verify convexity (R2)
        if (!isConvex(a, b, c, d)) {
            return false;
        }
        
        // Then check parallel sides (R3)
        bool parallel1 = isParallel(*a, *b, *c, *d);
        bool parallel2 = isParallel(*b, *c, *d, *a);
        
        return parallel1 || parallel2;
    }
    
    bool isConvex(vector<int>* a, vector<int>* b, vector<int>* c, vector<int>* d) {
        // Check if quadrilateral ABCD is convex using cross products
        auto cross = [](vector<int>* p1, vector<int>* p2, vector<int>* p3) {
            long long dx1 = (*p2)[0] - (*p1)[0];
            long long dy1 = (*p2)[1] - (*p1)[1];
            long long dx2 = (*p3)[0] - (*p2)[0];
            long long dy2 = (*p3)[1] - (*p2)[1];
            return dx1 * dy2 - dy1 * dx2;
        };
        
        long long c1 = cross(a, b, c);
        long long c2 = cross(b, c, d);
        long long c3 = cross(c, d, a);
        long long c4 = cross(d, a, b);
        
        return (c1 > 0 && c2 > 0 && c3 > 0 && c4 > 0) || 
               (c1 < 0 && c2 < 0 && c3 < 0 && c4 < 0);
    }
    
    bool isParallel(vector<int>& a, vector<int>& b, vector<int>& c, vector<int>& d) {
        long long dx1 = b[0] - a[0];
        long long dy1 = b[1] - a[1];
        long long dx2 = d[0] - c[0];
        long long dy2 = d[1] - c[1];
        
        return dy1 * dx2 == dy2 * dx1;
    }
};
# @lc code=end