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
        
        // Check if total sum is non-negative
        for (int b : balance) {
            total += b;
        }
        
        if (total < 0) return -1;
        
        long long minCost = LLONG_MAX;
        
        // Try each position as the cut point in the circular array
        for (int cut = 0; cut < n; cut++) {
            long long cost = 0;
            long long prefixSum = 0;
            
            // Compute cost for linearized array starting after the cut
            for (int i = 0; i < n - 1; i++) {
                int idx = (cut + 1 + i) % n;
                prefixSum += balance[idx];
                cost += abs(prefixSum);
            }
            
            minCost = min(minCost, cost);
        }
        
        return minCost;
    }
};
# @lc code=end