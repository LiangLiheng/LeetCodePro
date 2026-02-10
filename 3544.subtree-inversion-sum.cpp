#
# @lc app=leetcode id=3544 lang=cpp
#
# [3544] Subtree Inversion Sum
#
# @lc code=start
class Solution {
public:
    vector<vector<int>> adj;
    vector<int> nums;
    int k;
    unordered_map<string, long long> memo;
    
    string makeKey(int node, int parity, int dist) {
        return to_string(node) + "," + to_string(parity) + "," + to_string(dist);
    }
    
    long long dfs(int node, int parent, int parity, int dist) {
        string key = makeKey(node, parity, dist);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        long long result = LLONG_MIN;
        
        // Option 1: Don't invert this node
        long long current_val = (long long)nums[node] * (parity == 0 ? 1LL : -1LL);
        long long sum1 = current_val;
        for (int child : adj[node]) {
            if (child != parent) {
                sum1 += dfs(child, node, parity, min(dist + 1, k + 1));
            }
        }
        result = max(result, sum1);
        
        // Option 2: Invert this node (if allowed)
        if (dist >= k) {
            long long inverted_val = (long long)nums[node] * (parity == 0 ? -1LL : 1LL);
            long long sum2 = inverted_val;
            for (int child : adj[node]) {
                if (child != parent) {
                    sum2 += dfs(child, node, 1 - parity, 1);
                }
            }
            result = max(result, sum2);
        }
        
        memo[key] = result;
        return result;
    }
    
    long long subtreeInversionSum(vector<vector<int>>& edges, vector<int>& nums, int k) {
        int n = nums.size();
        this->nums = nums;
        this->k = k;
        adj.resize(n);
        
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        // Start from root 0, with parity 0 (no inversions yet), and distance k (can invert root)
        return dfs(0, -1, 0, k);
    }
};
# @lc code=end