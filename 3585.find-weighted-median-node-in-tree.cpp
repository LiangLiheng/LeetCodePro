#
# @lc app=leetcode id=3585 lang=cpp
#
# [3585] Find Weighted Median Node in Tree
#
# @lc code=start
class Solution {
public:
    vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        // Build adjacency list
        vector<vector<pair<int, long long>>> graph(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            long long w = edge[2];
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }
        
        vector<int> result;
        
        for (auto& query : queries) {
            int start = query[0], end = query[1];
            
            // BFS to find path
            vector<int> parent(n, -1);
            vector<long long> edgeWeight(n, 0);
            queue<int> q;
            q.push(start);
            parent[start] = start;
            
            while (!q.empty()) {
                int node = q.front();
                q.pop();
                
                if (node == end) break;
                
                for (auto& [neighbor, weight] : graph[node]) {
                    if (parent[neighbor] == -1) {
                        parent[neighbor] = node;
                        edgeWeight[neighbor] = weight;
                        q.push(neighbor);
                    }
                }
            }
            
            // Reconstruct path from start to end
            vector<int> path;
            vector<long long> weights;
            int curr = end;
            
            while (curr != start) {
                path.push_back(curr);
                weights.push_back(edgeWeight[curr]);
                curr = parent[curr];
            }
            path.push_back(start);
            
            // Reverse to get path from start to end
            reverse(path.begin(), path.end());
            reverse(weights.begin(), weights.end());
            
            // Calculate total weight
            long long totalWeight = 0;
            for (long long w : weights) {
                totalWeight += w;
            }
            
            // Find median node
            long long accumulated = 0;
            int medianNode = start;
            
            for (int i = 0; i < weights.size(); i++) {
                accumulated += weights[i];
                if (accumulated * 2 >= totalWeight) {
                    medianNode = path[i + 1];
                    break;
                }
            }
            
            result.push_back(medianNode);
        }
        
        return result;
    }
};
# @lc code=end