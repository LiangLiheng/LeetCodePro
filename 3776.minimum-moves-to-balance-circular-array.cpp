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
        
        // Check if solution is possible
        for (int x : balance) {
            total += x;
        }
        
        if (total < 0) return -1;
        
        long long minCost = LLONG_MAX;
        
        // Try all possible starting positions to linearize the circular array
        for (int start = 0; start < n; start++) {
            long long cost = 0;
            long long carry = 0;
            
            // Calculate cost for this linearization
            for (int i = 0; i < n - 1; i++) {
                carry += balance[(start + i) % n];
                cost += abs(carry);
            }
            
            minCost = min(minCost, cost);
        }
        
        return minCost;
    }
};
# @lc code=end