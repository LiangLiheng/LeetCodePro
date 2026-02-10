#
# @lc app=leetcode id=3562 lang=cpp
#
# [3562] Maximum Profit from Trading Stocks with Discounts
#
# @lc code=start
class Solution {
public:
    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        // Build adjacency list for tree
        vector<vector<int>> children(n + 1);
        for (auto& edge : hierarchy) {
            children[edge[0]].push_back(edge[1]);
        }
        
        // Memoization: (node, budgetLeft, parentBought) -> maxProfit
        map<tuple<int, int, int>, int> memo;
        
        function<int(int, int, int)> dfs = [&](int node, int budgetLeft, int parentBought) -> int {
            auto key = make_tuple(node, budgetLeft, parentBought);
            if (memo.count(key)) return memo[key];
            
            // Calculate cost and profit for current node
            int cost = parentBought ? present[node - 1] / 2 : present[node - 1];
            int profit = future[node - 1] - cost;
            
            // Option 1: Don't buy current node's stock
            // Use knapsack DP to allocate budget to children (no discount)
            vector<int> dpNoBuy(budgetLeft + 1, 0);
            for (int child : children[node]) {
                vector<int> newDp(budgetLeft + 1, 0);
                for (int b = 0; b <= budgetLeft; b++) {
                    newDp[b] = dpNoBuy[b]; // Don't allocate to this child
                    for (int cb = 1; cb <= b; cb++) {
                        newDp[b] = max(newDp[b], dpNoBuy[b - cb] + dfs(child, cb, 0));
                    }
                }
                dpNoBuy = newDp;
            }
            
            int maxProfit = dpNoBuy[budgetLeft];
            
            // Option 2: Buy current node's stock
            if (cost <= budgetLeft) {
                int remaining = budgetLeft - cost;
                // Use knapsack DP to allocate remaining budget to children (with discount)
                vector<int> dpBuy(remaining + 1, 0);
                for (int child : children[node]) {
                    vector<int> newDp(remaining + 1, 0);
                    for (int b = 0; b <= remaining; b++) {
                        newDp[b] = dpBuy[b];
                        for (int cb = 1; cb <= b; cb++) {
                            newDp[b] = max(newDp[b], dpBuy[b - cb] + dfs(child, cb, 1));
                        }
                    }
                    dpBuy = newDp;
                }
                maxProfit = max(maxProfit, profit + dpBuy[remaining]);
            }
            
            return memo[key] = maxProfit;
        };
        
        return dfs(1, budget, 0);
    }
};
# @lc code=end