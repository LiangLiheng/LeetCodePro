//
// @lc app=leetcode id=3710 lang=cpp
//
// [3710] Maximum Partition Factor
//
// @lc code=start
class Solution {
public:
    int manhattan(vector<int>& p1, vector<int>& p2) {
        return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
    }
    
    bool canPartition(vector<vector<int>>& points, int threshold, vector<int>& color) {
        int n = points.size();
        vector<vector<int>> adj(n);
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (manhattan(points[i], points[j]) < threshold) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        
        fill(color.begin(), color.end(), -1);
        
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
        
        int count0 = 0, count1 = 0;
        for (int c : color) {
            if (c == 0) count0++;
            else count1++;
        }
        
        return count0 > 0 && count1 > 0;
    }
    
    int maxPartitionFactor(vector<vector<int>>& points) {
        int n = points.size();
        
        if (n == 2) return 0;
        
        set<int> distSet;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                distSet.insert(manhattan(points[i], points[j]));
            }
        }
        
        vector<int> distances(distSet.begin(), distSet.end());
        sort(distances.rbegin(), distances.rend());
        
        int maxFactor = 0;
        
        for (int d : distances) {
            vector<int> color(n);
            if (canPartition(points, d, color)) {
                int min0 = INT_MAX, min1 = INT_MAX;
                
                for (int i = 0; i < n; i++) {
                    for (int j = i + 1; j < n; j++) {
                        if (color[i] == color[j]) {
                            int dist = manhattan(points[i], points[j]);
                            if (color[i] == 0) {
                                min0 = min(min0, dist);
                            } else {
                                min1 = min(min1, dist);
                            }
                        }
                    }
                }
                
                int count0 = 0, count1 = 0;
                for (int c : color) {
                    if (c == 0) count0++;
                    else count1++;
                }
                
                int factor;
                if (count0 == 1 && count1 == 1) {
                    factor = 0;
                } else if (count0 == 1) {
                    factor = min1;
                } else if (count1 == 1) {
                    factor = min0;
                } else {
                    factor = min(min0, min1);
                }
                
                maxFactor = max(maxFactor, factor);
            }
        }
        
        return maxFactor;
    }
};
// @lc code=end