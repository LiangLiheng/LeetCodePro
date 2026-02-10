/*
 * @lc app=leetcode id=3604 lang=cpp
 *
 * [3604] Minimum Time to Reach Destination in Directed Graph
 */

// @lc code=start
class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges) {
        // Build adjacency list: graph[u] = [(v, start, end), ...]
        vector<vector<tuple<int, int, int>>> graph(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], start = edge[2], end = edge[3];
            graph[u].push_back({v, start, end});
        }
        
        // Dijkstra's algorithm
        // Priority queue: (time, node)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        vector<int> dist(n, INT_MAX);
        
        pq.push({0, 0});
        dist[0] = 0;
        
        while (!pq.empty()) {
            auto [time, u] = pq.top();
            pq.pop();
            
            // Skip if we've already found a better path to u
            if (time > dist[u]) continue;
            
            // Try all outgoing edges from u
            for (auto [v, start, end] : graph[u]) {
                // We can only use this edge if time <= end
                if (time <= end) {
                    // The earliest we can use this edge is max(time, start)
                    int use_time = max(time, start);
                    // We arrive at v at time use_time + 1
                    int arrival_time = use_time + 1;
                    
                    if (arrival_time < dist[v]) {
                        dist[v] = arrival_time;
                        pq.push({arrival_time, v});
                    }
                }
            }
        }
        
        return dist[n-1] == INT_MAX ? -1 : dist[n-1];
    }
};
// @lc code=end