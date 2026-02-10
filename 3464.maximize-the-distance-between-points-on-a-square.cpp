#
# @lc app=leetcode id=3464 lang=cpp
#
# [3464] Maximize the Distance Between Points on a Square
#
# @lc code=start
class Solution {
public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        int n = points.size();
        
        // Precompute all pairwise Manhattan distances
        vector<vector<int>> dist(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                dist[i][j] = dist[j][i] = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
            }
        }
        
        // Binary search on the answer
        int left = 0, right = 4 * side;
        int result = 0;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canSelect(n, k, mid, dist)) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
private:
    bool canSelect(int n, int k, int minDist, vector<vector<int>>& dist) {
        vector<int> selected;
        return backtrack(n, k, minDist, 0, selected, dist);
    }
    
    bool backtrack(int n, int k, int minDist, int start, vector<int>& selected, vector<vector<int>>& dist) {
        if (selected.size() == k) {
            return true;
        }
        
        // Pruning: not enough remaining points
        if (n - start + selected.size() < k) {
            return false;
        }
        
        for (int i = start; i < n; i++) {
            bool valid = true;
            
            // Check if point i is valid (distance >= minDist from all selected points)
            for (int idx : selected) {
                if (dist[i][idx] < minDist) {
                    valid = false;
                    break;
                }
            }
            
            if (valid) {
                selected.push_back(i);
                if (backtrack(n, k, minDist, i + 1, selected, dist)) {
                    return true;
                }
                selected.pop_back();
            }
        }
        
        return false;
    }
};
# @lc code=end