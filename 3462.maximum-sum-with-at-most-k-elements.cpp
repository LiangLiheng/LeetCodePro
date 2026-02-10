#
# @lc app=leetcode id=3462 lang=cpp
#
# [3462] Maximum Sum With at Most K Elements
#
# @lc code=start
class Solution {
public:
    long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k) {
        vector<int> available;
        
        // For each row, get the top limits[i] elements
        for (int i = 0; i < grid.size(); i++) {
            vector<int> row = grid[i];
            sort(row.begin(), row.end(), greater<int>());
            
            int take = min(limits[i], (int)row.size());
            for (int j = 0; j < take; j++) {
                available.push_back(row[j]);
            }
        }
        
        // Sort all available elements in descending order
        sort(available.begin(), available.end(), greater<int>());
        
        // Sum the top k elements
        long long sum = 0;
        int count = min(k, (int)available.size());
        for (int i = 0; i < count; i++) {
            sum += available[i];
        }
        
        return sum;
    }
};
# @lc code=end