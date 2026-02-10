#
# @lc app=leetcode id=3604 lang=cpp
#
# [3604] Minimum Time to Reach Destination in Directed Graph
#
# @lc code=start
class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges) {
        // Build adjacency list: graph[u] = [[v, start, end], ...]
        vector<vector<vector<int>>> graph(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], start = edge[2], end = edge[3];
            graph[u].push_back({v, start, end});
        }
        
        // Dijkstra's algorithm with priority queue
        vector<int> dist(n, INT_MAX); // minimum time to reach each node
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // (time, node)
        
        dist[0] = 0;
        pq.push({0, 0});
        
        while (!pq.empty()) {
            auto [time, node] = pq.top();
            pq.pop();
            
            // If we reached the destination
            if (node == n - 1) {
                return time;
            }
            
            // Skip if we've already found a better path to this node
            if (time > dist[node]) {
                continue;
            }
            
            // Explore neighbors
            for (auto& edge : graph[node]) {
                int neighbor = edge[0];
                int start = edge[1];
                int end = edge[2];
                
                // If current time is beyond the edge's end time, skip
                if (time > end) {
                    continue;
                }
                
                // Calculate departure time (wait if necessary)
                int departureTime = max(time, start);
                int arrivalTime = departureTime + 1;
                
                // Update if we found a better path
                if (arrivalTime < dist[neighbor]) {
                    dist[neighbor] = arrivalTime;
                    pq.push({arrivalTime, neighbor});
                }
            }
        }
        
        // If we couldn't reach the destination
        return dist[n - 1] == INT_MAX ? -1 : dist[n - 1];
    }
};
# @lc code=end