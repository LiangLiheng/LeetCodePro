#
# @lc app=leetcode id=3367 lang=cpp
#
# [3367] Maximize Sum of Weights after Edge Removals
#
# @lc code=start
class Solution {
public:
    long long maximizeSumOfWeights(vector<vector<int>>& edges, int k) {
        int n = edges.size() + 1;
        vector<vector<pair<int, long long>>> adj(n);
        
        // Build adjacency list
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            long long w = e[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        // dp[node][0] = max sum when edge to parent is not included
        // dp[node][1] = max sum when edge to parent is included
        vector<array<long long, 2>> dp(n);
        
        function<void(int, int)> dfs = [&](int u, int parent) {
            vector<long long> gains;
            long long base = 0;
            
            for (auto [v, w] : adj[u]) {
                if (v == parent) continue;
                
                dfs(v, u);
                
                // Base: don't include any edge to children
                base += dp[v][0];
                
                // Gain from including edge (u, v)
                long long gain = w + dp[v][1] - dp[v][0];
                gains.push_back(gain);
            }
            
            // Sort gains in descending order
            sort(gains.rbegin(), gains.rend());
            
            // dp[u][0]: edge to parent not used, can use up to k edges to children
            dp[u][0] = base;
            for (int i = 0; i < min((int)gains.size(), k); i++) {
                if (gains[i] > 0) {
                    dp[u][0] += gains[i];
                }
            }
            
            // dp[u][1]: edge to parent used, can use up to k-1 edges to children
            dp[u][1] = base;
            for (int i = 0; i < min((int)gains.size(), k - 1); i++) {
                if (gains[i] > 0) {
                    dp[u][1] += gains[i];
                }
            }
        };
        
        dfs(0, -1);
        
        // Root node has no parent, so return dp[0][0]
        return dp[0][0];
    }
};
# @lc code=end