#
# @lc app=leetcode id=3419 lang=cpp
#
# [3419] Minimize the Maximum Edge Weight of Graph
#
# @lc code=start
class Solution {
public:
    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        // Collect all unique weights and sort them
        set<int> weight_set;
        for (const auto& e : edges) {
            weight_set.insert(e[2]);
        }
        vector<int> weights(weight_set.begin(), weight_set.end());
        
        // Binary search on the answer
        int left = 0, right = weights.size() - 1;
        int result = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int maxWeight = weights[mid];
            
            if (canReach(n, edges, threshold, maxWeight)) {
                result = maxWeight;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return result;
    }
    
private:
    bool canReach(int n, const vector<vector<int>>& edges, int threshold, int maxWeight) {
        // Build adjacency list with edges <= maxWeight
        vector<vector<pair<int, int>>> adj(n);
        
        for (const auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            if (w <= maxWeight) {
                adj[u].push_back({v, w});
            }
        }
        
        // For each node, keep only threshold smallest weight edges
        for (int u = 0; u < n; u++) {
            if (adj[u].size() > threshold) {
                sort(adj[u].begin(), adj[u].end(), 
                     [](const pair<int,int>& a, const pair<int,int>& b) {
                         return a.second < b.second;
                     });
                adj[u].resize(threshold);
            }
        }
        
        // Build reverse graph
        vector<vector<int>> rev_adj(n);
        for (int u = 0; u < n; u++) {
            for (const auto& [v, w] : adj[u]) {
                rev_adj[v].push_back(u);
            }
        }
        
        // BFS from node 0 in reverse graph
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(0);
        visited[0] = true;
        int count = 1;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : rev_adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                    count++;
                }
            }
        }
        
        return count == n;
    }
};
# @lc code=end