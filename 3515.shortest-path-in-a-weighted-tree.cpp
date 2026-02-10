#
# @lc app=leetcode id=3515 lang=cpp
#
# [3515] Shortest Path in a Weighted Tree
#
# @lc code=start
class Solution {
public:
    map<pair<int, int>, int> edgeWeight;
    vector<vector<int>> adj;
    
    vector<int> treeQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        adj.resize(n + 1);
        
        // Build adjacency list and edge weight map
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back(v);
            adj[v].push_back(u);
            int minNode = min(u, v), maxNode = max(u, v);
            edgeWeight[{minNode, maxNode}] = w;
        }
        
        vector<int> result;
        
        for (auto& q : queries) {
            if (q[0] == 1) {
                // Update edge weight
                int u = q[1], v = q[2], w = q[3];
                int minNode = min(u, v), maxNode = max(u, v);
                edgeWeight[{minNode, maxNode}] = w;
            } else {
                // Find distance from 1 to q[1]
                int target = q[1];
                if (target == 1) {
                    result.push_back(0);
                } else {
                    vector<bool> visited(n + 1, false);
                    int dist = dfs(1, target, visited);
                    result.push_back(dist);
                }
            }
        }
        
        return result;
    }
    
    int dfs(int node, int target, vector<bool>& visited) {
        if (node == target) return 0;
        
        visited[node] = true;
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                int minNode = min(node, neighbor), maxNode = max(node, neighbor);
                int weight = edgeWeight[{minNode, maxNode}];
                int dist = dfs(neighbor, target, visited);
                if (dist != -1) {
                    return weight + dist;
                }
            }
        }
        
        return -1;
    }
};
# @lc code=end