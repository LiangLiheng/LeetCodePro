#
# @lc app=leetcode id=3382 lang=cpp
#
# [3382] Maximum Area Rectangle With Point Constraints II
#
# @lc code=start
class Solution {
public:
    long long maxRectangleArea(vector<int>& xCoord, vector<int>& yCoord) {
        int n = xCoord.size();
        
        map<int, set<int>> xToY;
        
        for (int i = 0; i < n; i++) {
            xToY[xCoord[i]].insert(yCoord[i]);
        }
        
        long long maxArea = -1;
        
        vector<int> xVals;
        for (auto& [x, _] : xToY) {
            xVals.push_back(x);
        }
        
        for (int i = 0; i < xVals.size(); i++) {
            for (int j = i + 1; j < xVals.size(); j++) {
                int x1 = xVals[i], x2 = xVals[j];
                auto& ys1 = xToY[x1];
                auto& ys2 = xToY[x2];
                
                // Find common y-coordinates
                vector<int> commonY;
                for (int y : ys1) {
                    if (ys2.count(y)) {
                        commonY.push_back(y);
                    }
                }
                
                for (int p = 0; p < commonY.size(); p++) {
                    for (int q = p + 1; q < commonY.size(); q++) {
                        int y1 = commonY[p], y2 = commonY[q];
                        
                        // Check if any point is inside [x1, x2] × [y1, y2] other than corners
                        bool valid = true;
                        
                        // Only check x values between x1 and x2
                        for (int idx = i; idx <= j && valid; idx++) {
                            int x = xVals[idx];
                            
                            for (int y : xToY[x]) {
                                if (y < y1 || y > y2) continue;
                                
                                // Skip corners
                                if ((x == x1 && y == y1) || (x == x1 && y == y2) ||
                                    (x == x2 && y == y1) || (x == x2 && y == y2)) {
                                    continue;
                                }
                                
                                valid = false;
                                break;
                            }
                        }
                        
                        if (valid) {
                            long long area = (long long)(x2 - x1) * (y2 - y1);
                            maxArea = max(maxArea, area);
                        }
                    }
                }
            }
        }
        
        return maxArea;
    }
};
# @lc code=end