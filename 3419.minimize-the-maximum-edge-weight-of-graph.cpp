#
# @lc app=leetcode id=3419 lang=cpp
#
# [3419] Minimize the Maximum Edge Weight of Graph
#

# @lc code=start
class Solution {
public:
    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        auto check = [&](int x) -> bool {
            vector<vector<int>> g(n);
            for (const auto& e : edges) {
                if (e[2] <= x) {
                    g[e[1]].push_back(e[0]);
                }
            }
            vector<bool> vis(n, false);
            queue<int> q;
            q.push(0);
            vis[0] = true;
            int cnt = 1;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : g[u]) {
                    if (!vis[v]) {
                        vis[v] = true;
                        ++cnt;
                        q.push(v);
                    }
                }
            }
            return cnt == n;
        };
        int l = 0, r = 0;
        for (const auto& e : edges) {
            r = max(r, e[2]);
        }
        int ans = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (check(mid)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};
# @lc code=end