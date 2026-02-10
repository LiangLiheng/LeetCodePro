#
# @lc app=leetcode id=3786 lang=cpp
#
# [3786] Total Sum of Interaction Cost in Tree Groups
#
# @lc code=start
class Solution {
public:
    long long interactionCosts(int n, vector<vector<int>>& edges, vector<int>& group) {
        if (n == 1) return 0;
        
        // Build adjacency list
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        
        // Count total nodes in each group
        unordered_map<int, int> total_count;
        for (int g : group) {
            total_count[g]++;
        }
        
        long long result = 0;
        
        // DFS to compute subtree counts and contributions
        function<unordered_map<int, int>(int, int)> dfs = [&](int node, int parent) -> unordered_map<int, int> {
            unordered_map<int, int> subtree_count;
            subtree_count[group[node]] = 1;
            
            for (int child : adj[node]) {
                if (child != parent) {
                    auto child_count = dfs(child, node);
                    
                    // Calculate contribution of edge (node, child)
                    for (auto& [g, cnt] : child_count) {
                        int other_side = total_count[g] - cnt;
                        result += (long long)cnt * other_side;
                        // Merge child counts into current node
                        subtree_count[g] += cnt;
                    }
                }
            }
            
            return subtree_count;
        };
        
        dfs(0, -1);
        
        return result;
    }
};
# @lc code=end