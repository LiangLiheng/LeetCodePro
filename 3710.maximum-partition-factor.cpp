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
        
        // Compute all pairwise distances
        set<int> distSet;
        distSet.insert(0); // Include 0 as a candidate
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int dist = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                distSet.insert(dist);
            }
        }
        
        vector<int> distances(distSet.begin(), distSet.end());
        sort(distances.rbegin(), distances.rend()); // Sort in descending order
        
        // Try each distance from high to low
        for (int d : distances) {
            if (canAchieve(points, n, d)) {
                return d;
            }
        }
        
        return 0;
    }
    
private:
    bool canAchieve(vector<vector<int>>& points, int n, int d) {
        // Build conflict graph: edge (i,j) if distance < d
        vector<vector<int>> graph(n);
        bool hasEdges = false;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int dist = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                if (dist < d) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                    hasEdges = true;
                }
            }
        }
        
        // Special case: empty conflict graph means points can be freely partitioned
        if (!hasEdges) {
            return true; // Can put any point in group 1, rest in group 2
        }
        
        // Check if bipartite and both groups non-empty
        return isBipartite(graph, n);
    }
    
    bool isBipartite(vector<vector<int>>& graph, int n) {
        vector<int> color(n, -1);
        
        for (int start = 0; start < n; start++) {
            if (color[start] == -1) {
                queue<int> q;
                q.push(start);
                color[start] = 0;
                
                while (!q.empty()) {
                    int u = q.front();
                    q.pop();
                    
                    for (int v : graph[u]) {
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];
                            q.push(v);
                        } else if (color[v] == color[u]) {
                            return false; // Not bipartite
                        }
                    }
                }
            }
        }
        
        // Check if both groups are non-empty
        int count0 = 0, count1 = 0;
        for (int c : color) {
            if (c == 0) count0++;
            else count1++;
        }
        
        return count0 > 0 && count1 > 0;
    }
};
# @lc code=end