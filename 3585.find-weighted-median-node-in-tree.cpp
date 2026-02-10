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
        unordered_map<int, vector<pair<int, long long>>> graph;
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            long long w = edge[2];
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }
        
        vector<int> result;
        
        for (auto& query : queries) {
            int start = query[0], end = query[1];
            
            if (start == end) {
                result.push_back(start);
                continue;
            }
            
            // Find path from start to end using BFS
            unordered_map<int, int> parent;
            unordered_map<int, long long> edgeWeight;
            queue<int> q;
            unordered_set<int> visited;
            
            q.push(start);
            visited.insert(start);
            parent[start] = -1;
            
            while (!q.empty()) {
                int curr = q.front();
                q.pop();
                
                if (curr == end) break;
                
                for (auto& [neighbor, weight] : graph[curr]) {
                    if (visited.find(neighbor) == visited.end()) {
                        visited.insert(neighbor);
                        parent[neighbor] = curr;
                        edgeWeight[neighbor] = weight;
                        q.push(neighbor);
                    }
                }
            }
            
            // Reconstruct path
            vector<int> path;
            vector<long long> weights;
            int curr = end;
            while (curr != -1) {
                path.push_back(curr);
                if (parent[curr] != -1) {
                    weights.push_back(edgeWeight[curr]);
                }
                curr = parent[curr];
            }
            
            reverse(path.begin(), path.end());
            reverse(weights.begin(), weights.end());
            
            // Calculate total weight
            long long totalWeight = 0;
            for (auto w : weights) {
                totalWeight += w;
            }
            
            // Find median node
            long long cumWeight = 0;
            int medianNode = start;
            
            for (int i = 0; i < weights.size(); i++) {
                cumWeight += weights[i];
                if (cumWeight * 2 >= totalWeight) {
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