#
# @lc app=leetcode id=3786 lang=cpp
#
# [3786] Total Sum of Interaction Cost in Tree Groups
#
# @lc code=start
class Solution {
public:
    long long interactionCosts(int n, vector<vector<int>>& edges, vector<int>& group) {
        // Build adjacency list
        vector<vector<int>> adj(n);
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        // Count total nodes of each group
        vector<int> totalCount(21, 0);
        for (int g : group) {
            totalCount[g]++;
        }
        
        long long result = 0;
        
        // DFS to calculate contribution of each edge
        function<vector<int>(int, int)> dfs = [&](int node, int parent) -> vector<int> {
            // Count nodes of each group in subtree rooted at node
            vector<int> count(21, 0);
            count[group[node]]++;
            
            for (int child : adj[node]) {
                if (child == parent) continue;
                
                vector<int> childCount = dfs(child, node);
                
                // Calculate contribution of edge (node, child)
                for (int g = 1; g <= 20; g++) {
                    long long inChild = childCount[g];
                    long long notInChild = totalCount[g] - childCount[g];
                    result += inChild * notInChild;
                }
                
                // Merge childCount into count
                for (int g = 1; g <= 20; g++) {
                    count[g] += childCount[g];
                }
            }
            
            return count;
        };
        
        dfs(0, -1);
        
        return result;
    }
};
# @lc code=end