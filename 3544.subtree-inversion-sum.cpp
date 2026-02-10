#
# @lc app=leetcode id=3544 lang=cpp
#
# [3544] Subtree Inversion Sum
#
# @lc code=start
class Solution {
public:
    long long subtreeInversionSum(vector<vector<int>>& edges, vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        
        map<tuple<int,int,int>, long long> memo;
        
        function<long long(int, int, int, int)> dfs = [&](int u, int parent, int d, int p) -> long long {
            auto key = make_tuple(u, d, p);
            if (memo.count(key)) return memo[key];
            
            int sign = (p == 0) ? 1 : -1;
            long long result = LLONG_MIN;
            
            vector<int> children;
            for (int v : adj[u]) {
                if (v != parent) {
                    children.push_back(v);
                }
            }
            
            // Option 1: Don't invert at u
            {
                long long sum = (long long)nums[u] * sign;
                int child_d = min(d + 1, k);
                for (int v : children) {
                    sum += dfs(v, u, child_d, p);
                }
                result = max(result, sum);
            }
            
            // Option 2: Invert at u (only if d >= k)
            if (d >= k) {
                long long sum = (long long)nums[u] * (-sign);
                for (int v : children) {
                    sum += dfs(v, u, 1, 1 - p);
                }
                result = max(result, sum);
            }
            
            return memo[key] = result;
        };
        
        return dfs(0, -1, k, 0);
    }
};
# @lc code=end