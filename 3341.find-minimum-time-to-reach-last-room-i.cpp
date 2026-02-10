#
# @lc app=leetcode id=3341 lang=cpp
#
# [3341] Find Minimum Time to Reach Last Room I
#

# @lc code=start
class Solution {
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int rows = moveTime.size();
        int cols = moveTime[0].size();
        vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
        dist[0][0] = 0;
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        pq.push({0, 0, 0});
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        while (!pq.empty()) {
            auto [time, r, c] = pq.top(); pq.pop();
            if (time > dist[r][c]) continue;
            for (auto& dir : dirs) {
                int nr = r + dir[0];
                int nc = c + dir[1];
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                    int new_time = max(time, moveTime[nr][nc]) + 1;
                    if (new_time < dist[nr][nc]) {
                        dist[nr][nc] = new_time;
                        pq.push({new_time, nr, nc});
                    }
                }
            }
        }
        return dist[rows - 1][cols - 1];
    }
};
# @lc code=end