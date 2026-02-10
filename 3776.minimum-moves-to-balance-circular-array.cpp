#
# @lc app=leetcode id=3776 lang=cpp
#
# [3776] Minimum Moves to Balance Circular Array
#
# @lc code=start
class Solution {
public:
    long long minMoves(vector<int>& balance) {
        int n = balance.size();
        long long total = 0;
        bool has_negative = false;
        
        // Check if solution exists and if there's any negative value
        for (int i = 0; i < n; i++) {
            total += balance[i];
            if (balance[i] < 0) has_negative = true;
        }
        
        // If total sum is negative, impossible to make all non-negative
        if (total < 0) return -1;
        
        // If no negative values, already balanced
        if (!has_negative) return 0;
        
        long long min_cost = LLONG_MAX;
        
        // Try breaking the circle at each position
        for (int break_point = 0; break_point < n; break_point++) {
            long long cost = 0;
            long long prefix_sum = 0;
            
            // Calculate cost for this linearization
            for (int i = 0; i < n - 1; i++) {
                int idx = (break_point + i) % n;
                prefix_sum += balance[idx];
                // Cost is the absolute flow through this edge
                cost += abs(prefix_sum);
            }
            
            min_cost = min(min_cost, cost);
        }
        
        return min_cost;
    }
};
# @lc code=end