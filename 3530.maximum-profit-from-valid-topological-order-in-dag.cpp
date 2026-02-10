#
# @lc app=leetcode id=3530 lang=cpp
#
# [3530] Maximum Profit from Valid Topological Order in DAG
#
# @lc code=start
class Solution {
public:
    int maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {
        // Build prerequisites list for each node
        vector<vector<int>> prerequisites(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            prerequisites[v].push_back(u);  // v depends on u
        }
        
        // DP with bitmask
        // dp[mask] = maximum profit when nodes in mask are processed
        vector<int> dp(1 << n, -1);
        dp[0] = 0;
        
        for (int mask = 0; mask < (1 << n); mask++) {
            if (dp[mask] == -1) continue;
            
            int position = __builtin_popcount(mask) + 1;  // Next position (1-based)
            
            // Try adding each unprocessed node
            for (int node = 0; node < n; node++) {
                if (mask & (1 << node)) continue;  // Node already processed
                
                // Check if all prerequisites are satisfied
                bool canAdd = true;
                for (int prereq : prerequisites[node]) {
                    if (!(mask & (1 << prereq))) {
                        canAdd = false;
                        break;
                    }
                }
                
                if (canAdd) {
                    int newMask = mask | (1 << node);
                    int newProfit = dp[mask] + score[node] * position;
                    dp[newMask] = max(dp[newMask], newProfit);
                }
            }
        }
        
        return dp[(1 << n) - 1];
    }
};
# @lc code=end