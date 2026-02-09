#
# @lc app=leetcode id=3341 lang=cpp
#
# [3341] Find Minimum Time to Reach Last Room I
#
# @lc code=start
class Solution {
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int n = moveTime.size();
        int m = moveTime[0].size();
        
        // Priority queue: {time, {row, col}}
        priority_queue<pair<int, pair<int, int>>, 
                      vector<pair<int, pair<int, int>>>,
                      greater<pair<int, pair<int, int>>>> pq;
        
        // Distance array
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        
        // Start from (0, 0) at time 0
        pq.push({0, {0, 0}});
        dist[0][0] = 0;
        
        // Directions: up, down, left, right
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        while (!pq.empty()) {
            auto [time, pos] = pq.top();
            pq.pop();
            
            int x = pos.first;
            int y = pos.second;
            
            // If we reached the destination
            if (x == n - 1 && y == m - 1) {
                return time;
            }
            
            // If this is not the optimal path to this cell, skip
            if (time > dist[x][y]) {
                continue;
            }
            
            // Explore neighbors
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                
                // Check bounds
                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    // Calculate arrival time to (nx, ny)
                    // We can start moving at max(current_time, moveTime[nx][ny])
                    // And it takes 1 second to move
                    int newTime = max(time, moveTime[nx][ny]) + 1;
                    
                    // Update if we found a better path
                    if (newTime < dist[nx][ny]) {
                        dist[nx][ny] = newTime;
                        pq.push({newTime, {nx, ny}});
                    }
                }
            }
        }
        
        return dist[n - 1][m - 1];
    }
};
# @lc code=end