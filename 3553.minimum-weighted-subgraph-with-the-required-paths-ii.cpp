#
# @lc app=leetcode id=3553 lang=cpp
#
# [3553] Minimum Weighted Subgraph With the Required Paths II
#
# @lc code=start
class Solution {
public:
    vector<vector<pair<int, long long>>> adj;
    
    vector<long long> bfs(int src, int n) {
        vector<long long> dist(n, LLONG_MAX);
        queue<int> q;
        q.push(src);
        dist[src] = 0;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (auto [v, w] : adj[u]) {
                if (dist[v] == LLONG_MAX) {
                    dist[v] = dist[u] + w;
                    q.push(v);
                }
            }
        }
        return dist;
    }
    
    vector<int> minimumWeight(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        adj.resize(n);
        
        // Build adjacency list
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        vector<int> answer;
        
        for (auto& q : queries) {
            int src1 = q[0], src2 = q[1], dest = q[2];
            
            // Calculate distances from all three nodes
            vector<long long> dist1 = bfs(src1, n);
            vector<long long> dist2 = bfs(src2, n);
            vector<long long> distDest = bfs(dest, n);
            
            long long minWeight = LLONG_MAX;
            
            // Try each node as potential junction
            for (int junction = 0; junction < n; junction++) {
                if (dist1[junction] != LLONG_MAX && 
                    dist2[junction] != LLONG_MAX && 
                    distDest[junction] != LLONG_MAX) {
                    long long totalWeight = dist1[junction] + dist2[junction] + distDest[junction];
                    minWeight = min(minWeight, totalWeight);
                }
            }
            
            answer.push_back((int)minWeight);
        }
        
        return answer;
    }
};
# @lc code=end