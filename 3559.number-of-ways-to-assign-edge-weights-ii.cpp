#
# @lc app=leetcode id=3559 lang=cpp
#
# [3559] Number of Ways to Assign Edge Weights II
#
# @lc code=start
class Solution {
public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        const int MOD = 1e9 + 7;
        int n = edges.size() + 1;
        
        // Build adjacency list
        vector<vector<int>> graph(n + 1);
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        vector<int> result;
        
        for (auto& query : queries) {
            int u = query[0];
            int v = query[1];
            
            if (u == v) {
                result.push_back(0);
                continue;
            }
            
            // Find path from u to v using BFS
            int pathLength = findPathLength(graph, u, v, n);
            
            if (pathLength == 0) {
                result.push_back(0);
            } else {
                // Calculate 2^(pathLength - 1) mod MOD
                long long ans = modPow(2, pathLength - 1, MOD);
                result.push_back(ans);
            }
        }
        
        return result;
    }
    
private:
    int findPathLength(vector<vector<int>>& graph, int start, int end, int n) {
        if (start == end) return 0;
        
        queue<pair<int, int>> q;  // {node, distance}
        vector<bool> visited(n + 1, false);
        
        q.push({start, 0});
        visited[start] = true;
        
        while (!q.empty()) {
            auto [node, dist] = q.front();
            q.pop();
            
            if (node == end) {
                return dist;
            }
            
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push({neighbor, dist + 1});
                }
            }
        }
        
        return 0;
    }
    
    long long modPow(long long base, long long exp, long long mod) {
        long long result = 1;
        base %= mod;
        while (exp > 0) {
            if (exp % 2 == 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exp /= 2;
        }
        return result;
    }
};
# @lc code=end