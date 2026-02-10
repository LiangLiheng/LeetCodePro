#
# @lc app=leetcode id=3562 lang=cpp
#
# [3562] Maximum Profit from Trading Stocks with Discounts
#
# @lc code=start
class Solution {
public:
    vector<vector<int>> children;
    vector<int> present, future;
    map<tuple<int, int, bool>, int> memo;
    
    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        this->present = present;
        this->future = future;
        children.resize(n + 1);
        
        for (auto& edge : hierarchy) {
            children[edge[0]].push_back(edge[1]);
        }
        
        return dfs(1, budget, false);
    }
    
    int dfs(int node, int budget, bool parentBought) {
        auto key = make_tuple(node, budget, parentBought);
        if (memo.count(key)) {
            return memo[key];
        }
        
        int cost = parentBought ? (present[node - 1] / 2) : present[node - 1];
        int nodeProfit = future[node - 1] - cost;
        
        // Option 1: Don't buy at this node
        int result = solveChildren(children[node], budget, false);
        
        // Option 2: Buy at this node (if budget allows)
        if (budget >= cost) {
            int buyResult = nodeProfit + solveChildren(children[node], budget - cost, true);
            result = max(result, buyResult);
        }
        
        return memo[key] = result;
    }
    
    int solveChildren(const vector<int>& childList, int budget, bool parentBought) {
        if (childList.empty()) return 0;
        
        int k = childList.size();
        // dp[i][b] = max profit from first i children using at most budget b
        vector<vector<int>> dp(k + 1, vector<int>(budget + 1, 0));
        
        for (int i = 0; i < k; i++) {
            int child = childList[i];
            for (int b = 0; b <= budget; b++) {
                // Option 1: Don't give any budget to child i
                dp[i + 1][b] = dp[i][b];
                
                // Option 2: Give some budget to child i
                for (int give = 0; give <= b; give++) {
                    int childProfit = dfs(child, give, parentBought);
                    dp[i + 1][b] = max(dp[i + 1][b], dp[i][b - give] + childProfit);
                }
            }
        }
        
        return dp[k][budget];
    }
};
# @lc code=end