#
# @lc app=leetcode id=3530 lang=cpp
#
# [3530] Maximum Profit from Valid Topological Order in DAG
#

# @lc code=start
class Solution {
public:
    int maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {
        vector<int> pred_mask(n, 0);
        for (const auto& e : edges) {
            pred_mask[e[1]] |= (1 << e[0]);
        }
        int N = 1 << n;
        vector<long long> dp(N, -1);
        dp[0] = 0;
        for (int s = 0; s < N; ++s) {
            for (int v = 0; v < n; ++v) {
                if ((s & (1 << v)) == 0) continue;
                if ((pred_mask[v] & s) != pred_mask[v]) continue;
                int prev = s ^ (1 << v);
                if (dp[prev] != -1) {
                    long long profit = dp[prev] + 1LL * score[v] * __builtin_popcount(s);
                    if (dp[s] == -1 || profit > dp[s]) {
                        dp[s] = profit;
                    }
                }
            }
        }
        return static_cast<int>(dp[N - 1]);
    }
};
# @lc code=end