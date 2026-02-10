#
# @lc app=leetcode id=3486 lang=cpp
#
# [3486] Longest Special Path II
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = edges.size() + 1;
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        const int MAX_VAL = 50010;
        vector<deque<int>> occs(MAX_VAL);
        multiset<int> high_blockers, dup_firsts;
        vector<int> path, prefix_len;
        path.reserve(n);
        prefix_len.reserve(n);
        int max_len = 0;
        int min_nodes = INT_MAX;
        auto dfs = [&](auto&& self, int u, int p, int cum_len) -> void {
            int x = nums[u];
            int pos = path.size();
            size_t old_cnt = occs[x].size();
            // Erase old contributions
            if (old_cnt >= 3) {
                int blk = occs[x][old_cnt - 3] + 1;
                auto it = high_blockers.find(blk);
                if (it != high_blockers.end()) high_blockers.erase(it);
            }
            if (old_cnt == 2) {
                int first_pos = occs[x].front();
                auto it = dup_firsts.find(first_pos);
                if (it != dup_firsts.end()) dup_firsts.erase(it);
            }
            // Add occurrence
            occs[x].push_back(pos);
            size_t new_cnt = occs[x].size();
            // Insert new contributions
            if (new_cnt >= 3) {
                int blk = occs[x][new_cnt - 3] + 1;
                high_blockers.insert(blk);
            }
            if (new_cnt == 2) {
                int first_pos = occs[x].front();
                dup_firsts.insert(first_pos);
            }
            // Push path and prefix
            path.push_back(u);
            prefix_len.push_back(cum_len);
            // Compute blocker
            int blocker = 0;
            if (!high_blockers.empty()) {
                blocker = max(blocker, *high_blockers.rbegin());
            }
            if (dup_firsts.size() >= 2) {
                auto it = dup_firsts.rbegin();
                ++it;
                blocker = max(blocker, *it + 1);
            }
            // Suffix metrics
            int start = blocker;
            int prev = (start == 0 ? 0 : prefix_len[start]);
            int this_len = prefix_len.back() - prev;
            int this_nod = static_cast<int>(path.size()) - start;
            if (this_len > max_len) {
                max_len = this_len;
                min_nodes = this_nod;
            } else if (this_len == max_len) {
                min_nodes = min(min_nodes, this_nod);
            }
            // Recur children
            for (auto [v, w] : adj[u]) {
                if (v == p) continue;
                self(self, v, u, cum_len + w);
            }
            // Backtrack
            if (new_cnt >= 3) {
                int blk = occs[x][new_cnt - 3] + 1;
                auto it = high_blockers.find(blk);
                if (it != high_blockers.end()) high_blockers.erase(it);
            }
            if (new_cnt == 2) {
                int first_pos = occs[x].front();
                auto it = dup_firsts.find(first_pos);
                if (it != dup_firsts.end()) dup_firsts.erase(it);
            }
            occs[x].pop_back();
            if (old_cnt >= 3) {
                int blk = occs[x][old_cnt - 3] + 1;
                high_blockers.insert(blk);
            }
            if (old_cnt == 2) {
                int first_pos = occs[x].front();
                dup_firsts.insert(first_pos);
            }
            path.pop_back();
            prefix_len.pop_back();
        };
        dfs(dfs, 0, -1, 0);
        return {max_len, min_nodes};
    }
};
# @lc code=end