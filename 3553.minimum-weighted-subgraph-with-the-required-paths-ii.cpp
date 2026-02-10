#
# @lc app=leetcode id=3553 lang=cpp
#
# [3553] Minimum Weighted Subgraph With the Required Paths II
#
# @lc code=start
class Solution {
public:
    vector<int> minimumWeight(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        
        // Build adjacency list
        vector<vector<pair<int, int>>> graph(n);
        map<pair<int, int>, int> edgeWeight;
        
        for (const auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
            edgeWeight[{min(u, v), max(u, v)}] = w;
        }
        
        vector<int> result;
        
        for (const auto& q : queries) {
            int src1 = q[0], src2 = q[1], dest = q[2];
            
            set<pair<int, int>> path1Edges = findPath(graph, src1, dest, n);
            set<pair<int, int>> path2Edges = findPath(graph, src2, dest, n);
            
            set<pair<int, int>> allEdges = path1Edges;
            allEdges.insert(path2Edges.begin(), path2Edges.end());
            
            int totalWeight = 0;
            for (const auto& e : allEdges) {
                totalWeight += edgeWeight[e];
            }
            
            result.push_back(totalWeight);
        }
        
        return result;
    }
    
private:
    set<pair<int, int>> findPath(const vector<vector<pair<int, int>>>& graph, int start, int end, int n) {
        vector<int> parent(n, -1);
        queue<int> q;
        q.push(start);
        vector<bool> visited(n, false);
        visited[start] = true;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            if (u == end) break;
            
            for (const auto& [v, w] : graph[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }
        
        set<pair<int, int>> pathEdges;
        int curr = end;
        while (parent[curr] != -1) {
            int p = parent[curr];
            pathEdges.insert({min(curr, p), max(curr, p)});
            curr = p;
        }
        
        return pathEdges;
    }
};
# @lc code=end