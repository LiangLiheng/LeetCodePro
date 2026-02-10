#
# @lc app=leetcode id=3786 lang=cpp
#
# [3786] Total Sum of Interaction Cost in Tree Groups
#

# @lc code=start
class Solution {
public:
    long long interactionCosts(int n, vector<vector<int>>& edges, vector<int>& group) {
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        long long answer = 0;
        for (int g = 1; g <= 20; ++g) {
            int total_cnt = 0;
            for (int i = 0; i < n; ++i) {
                if (group[i] == g) ++total_cnt;
            }
            if (total_cnt < 2) continue;
            long long contrib = 0;
            auto dfs = [&](auto&& self, int u, int par) -> int {
                int sz = (group[u] == g ? 1 : 0);
                for (int v : adj[u]) {
                    if (v == par) continue;
                    int s = self(self, v, u);
                    contrib += 1LL * s * (total_cnt - s);
                    sz += s;
                }
                return sz;
            };
            dfs(dfs, 0, -1);
            answer += contrib;
        }
        return answer;
    }
};
# @lc code=end