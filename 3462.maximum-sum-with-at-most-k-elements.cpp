#
# @lc app=leetcode id=3462 lang=cpp
#
# [3462] Maximum Sum With at Most K Elements
#

# @lc code=start
class Solution {
public:
    long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k) {
        int n = grid.size();
        if (n == 0) return 0;
        vector<int> cand;
        for (int i = 0; i < n; ++i) {
            vector<int> row = grid[i];
            sort(row.rbegin(), row.rend());
            int lim = limits[i];
            for (int j = 0; j < lim && j < (int)row.size(); ++j) {
                cand.push_back(row[j]);
            }
        }
        sort(cand.rbegin(), cand.rend());
        long long sum = 0;
        for (size_t i = 0; i < cand.size() && i < (size_t)k; ++i) {
            sum += cand[i];
        }
        return sum;
    }
};
# @lc code=end