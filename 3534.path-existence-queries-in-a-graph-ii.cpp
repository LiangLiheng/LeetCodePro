#
# @lc app=leetcode id=3534 lang=cpp
#
# [3534] Path Existence Queries in a Graph II
#
# @lc code=start
class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // Build adjacency list
        vector<vector<int>> graph(n);
        
        // Sort nodes by their values to optimize edge finding
        vector<pair<int, int>> sorted_nodes; // {value, index}
        for (int i = 0; i < n; i++) {
            sorted_nodes.push_back({nums[i], i});
        }
        sort(sorted_nodes.begin(), sorted_nodes.end());
        
        // Build edges efficiently
        for (int i = 0; i < n; i++) {
            int idx1 = sorted_nodes[i].second;
            int val1 = sorted_nodes[i].first;
            
            // Check forward in sorted order
            for (int j = i + 1; j < n; j++) {
                int idx2 = sorted_nodes[j].second;
                int val2 = sorted_nodes[j].first;
                
                if (val2 - val1 > maxDiff) break;
                
                graph[idx1].push_back(idx2);
                graph[idx2].push_back(idx1);
            }
        }
        
        // Process queries
        vector<int> answer;
        for (auto& query : queries) {
            int u = query[0];
            int v = query[1];
            
            if (u == v) {
                answer.push_back(0);
                continue;
            }
            
            // BFS to find shortest path
            vector<int> dist(n, -1);
            queue<int> q;
            q.push(u);
            dist[u] = 0;
            
            while (!q.empty()) {
                int curr = q.front();
                q.pop();
                
                if (curr == v) {
                    break;
                }
                
                for (int neighbor : graph[curr]) {
                    if (dist[neighbor] == -1) {
                        dist[neighbor] = dist[curr] + 1;
                        q.push(neighbor);
                    }
                }
            }
            
            answer.push_back(dist[v]);
        }
        
        return answer;
    }
};
# @lc code=end