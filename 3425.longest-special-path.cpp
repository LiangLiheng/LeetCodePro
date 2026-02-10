#
# @lc app=leetcode id=3425 lang=cpp
#
# [3425] Longest Special Path
#

# @lc code=start
class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = nums.size();
        vector<vector<pair<int,int>>> adj(n);
        for(const auto& e : edges) {
            int u = e[0], v = e[1], len = e[2];
            adj[u].emplace_back(v, len);
            adj[v].emplace_back(u, len);
        }
        long long max_len = 0;
        int min_nodes_cnt = 1;
        vector<long long> path_dist;
        unordered_map<int, int> last_seen;
        int window_left = 0;
        auto dfs = [&](auto&& self, int u, int par, long long cur_dist, int cur_dep) -> void {
            int val = nums[u];
            int old_window = window_left;
            auto it = last_seen.find(val);
            bool existed = (it != last_seen.end());
            int prev_dep = existed ? it->second : -1;
            if (existed && prev_dep >= window_left) {
                window_left = prev_dep + 1;
            }
            int old_dep_val = prev_dep;
            last_seen[val] = cur_dep;
            path_dist.push_back(cur_dist);
            int suf_nodes = cur_dep - window_left + 1;
            long long suf_len = path_dist[cur_dep] - path_dist[window_left];
            if (suf_len > max_len) {
                max_len = suf_len;
                min_nodes_cnt = suf_nodes;
            } else if (suf_len == max_len) {
                min_nodes_cnt = std::min(min_nodes_cnt, suf_nodes);
            }
            for (const auto& p : adj[u]) {
                int v = p.first;
                int w = p.second;
                if (v != par) {
                    self(self, v, u, cur_dist + w, cur_dep + 1);
                }
            }
            path_dist.pop_back();
            if (existed) {
                last_seen[val] = old_dep_val;
            } else {
                last_seen.erase(val);
            }
            window_left = old_window;
        };
        dfs(dfs, 0, -1, 0LL, 0);
        return {(int)max_len, min_nodes_cnt};
    }
};
# @lc code=end