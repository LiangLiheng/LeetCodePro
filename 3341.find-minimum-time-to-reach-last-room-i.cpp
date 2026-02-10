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
        vector<vector<long long>> dist(n, vector<long long>(m, LLONG_MAX / 2));
        dist[0][0] = 0;
        using ll = long long;
        priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<tuple<ll, int, int>>> pq;
        pq.push({0LL, 0, 0});
        int di[4] = {-1, 0, 1, 0};
        int dj[4] = {0, 1, 0, -1};
        while (!pq.empty()) {
            auto [time, i, j] = pq.top(); pq.pop();
            if (time > dist[i][j]) continue;
            for (int d = 0; d < 4; ++d) {
                int ni = i + di[d];
                int nj = j + dj[d];
                if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                    ll ntime = max(time, (ll)moveTime[ni][nj]) + 1;
                    if (ntime < dist[ni][nj]) {
                        dist[ni][nj] = ntime;
                        pq.push({ntime, ni, nj});
                    }
                }
            }
        }
        return dist[n - 1][m - 1];
    }
};
# @lc code=end