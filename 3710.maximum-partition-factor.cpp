#
# @lc app=leetcode id=3710 lang=cpp
#
# [3710] Maximum Partition Factor
#
# @lc code=start
class Solution {
public:
    int maxPartitionFactor(vector<vector<int>>& points) {
        int n = points.size();
        
        // Special case: n = 2
        if (n == 2) return 0;
        
        // Calculate all pairwise distances
        vector<int> distances;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int dist = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                distances.push_back(dist);
            }
        }
        
        // Sort distances for binary search candidates
        sort(distances.begin(), distances.end());
        distances.erase(unique(distances.begin(), distances.end()), distances.end());
        
        // Binary search on the answer
        int answer = 0;
        int left = 0, right = distances.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int d = distances[mid];
            
            // Check if we can achieve partition factor >= d
            if (canPartition(points, d)) {
                answer = d;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return answer;
    }
    
private:
    bool canPartition(vector<vector<int>>& points, int d) {
        int n = points.size();
        
        // Build adjacency list for points with distance < d
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int dist = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                if (dist < d) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        
        // Check if graph is bipartite using BFS
        vector<int> color(n, -1);
        
        for (int start = 0; start < n; start++) {
            if (color[start] != -1) continue;
            
            queue<int> q;
            q.push(start);
            color[start] = 0;
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                
                for (int v : adj[u]) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        return false;
                    }
                }
            }
        }
        
        // Check that both groups are non-empty
        bool has0 = false, has1 = false;
        for (int c : color) {
            if (c == 0) has0 = true;
            if (c == 1) has1 = true;
        }
        
        return has0 && has1;
    }
};
# @lc code=end