#
# @lc app=leetcode id=3493 lang=cpp
#
# [3493] Properties Graph
#
# @lc code=start
class Solution {
public:
    int intersect(vector<int>& a, vector<int>& b) {
        unordered_set<int> setA(a.begin(), a.end());
        unordered_set<int> setB(b.begin(), b.end());
        
        int count = 0;
        for (int val : setA) {
            if (setB.count(val)) {
                count++;
            }
        }
        return count;
    }
    
    void dfs(int node, vector<vector<int>>& graph, vector<bool>& visited) {
        visited[node] = true;
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, graph, visited);
            }
        }
    }
    
    int numberOfComponents(vector<vector<int>>& properties, int k) {
        int n = properties.size();
        vector<vector<int>> graph(n);
        
        // Build the graph
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (intersect(properties[i], properties[j]) >= k) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }
        
        // Count connected components using DFS
        vector<bool> visited(n, false);
        int components = 0;
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, graph, visited);
                components++;
            }
        }
        
        return components;
    }
};
# @lc code=end