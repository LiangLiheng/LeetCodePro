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
        if (n == 2) return 0;
        auto mandist = [&](int i, int j) -> long long {
            return std::abs(static_cast<long long>(points[i][0]) - points[j][0]) +
                   std::abs(static_cast<long long>(points[i][1]) - points[j][1]);
        };
        long long max_d = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                max_d = std::max(max_d, mandist(i, j));
            }
        }
        long long lo = 0, hi = max_d + 1;
        while (lo < hi) {
            long long mid = lo + (hi - lo + 1) / 2;
            vector<vector<int>> adj(n);
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    if (mandist(i, j) < mid) {
                        adj[i].push_back(j);
                        adj[j].push_back(i);
                    }
                }
            }
            vector<int> color(n, 0);
            auto bfs_visit = [&](int start) -> bool {
                std::queue<int> q;
                color[start] = 1;
                q.push(start);
                while (!q.empty()) {
                    int u = q.front(); q.pop();
                    for (int v : adj[u]) {
                        if (color[v] == 0) {
                            color[v] = 3 - color[u];
                            q.push(v);
                        } else if (color[v] == color[u]) {
                            return false;
                        }
                    }
                }
                return true;
            };
            bool possible = true;
            for (int i = 0; i < n; ++i) {
                if (color[i] == 0) {
                    if (!bfs_visit(i)) {
                        possible = false;
                        break;
                    }
                }
            }
            if (possible) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return static_cast<int>(lo);
    }
};
# @lc code=end